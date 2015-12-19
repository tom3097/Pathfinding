#include "PathFinder.h"


PathFinder::PathFinder()
{

}


PathFinder::~PathFinder()
{

}


unsigned PathFinder::calculateManhattanH(const Field& from, const Field& to)
{
	return std::abs(from.getCoords().getX() - to.getCoords().getX()) + std::abs(from.getCoords().getY() - to.getCoords().getY());
}


bool PathFinder::CompareFields::operator() (const Field& field1, const Field& field2)
{
	return field1.getF() > field2.getF();
}


/* A star algorithm */
void PathFinder::A_star_algorithm(Raster& raster) {
	std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

	/* Prepare raster for this algorithm */
	for (int m_idx = 0; m_idx < raster.getM(); ++m_idx)
	{
		for (int n_idx = 0; n_idx < raster.getN(); ++n_idx)
		{
			raster.getField(m_idx, n_idx).updateGHF(0, 0);
		}
	}

	typedef std::priority_queue<std::reference_wrapper<Field>, std::vector<std::reference_wrapper<Field> >, PathFinder::CompareFields> Queue;

	bool** matOL = new bool*[raster.getM()];
	for (int idx = 0; idx < raster.getM(); ++idx)
		matOL[idx] = new bool[raster.getN()];

	bool** matCL = new bool*[raster.getM()];
	for (int idx = 0; idx < raster.getM(); ++idx)
		matCL[idx] = new bool[raster.getN()];

	for (int l_idx = 0; l_idx < raster.getM(); ++l_idx)
	{
		for (int c_idx = 0; c_idx < raster.getN(); ++c_idx)
		{
			matOL[l_idx][c_idx] = false;
			matCL[l_idx][c_idx] = false;
		}
	}

	Queue queueOL;

	queueOL.push(std::ref(raster.getBegin()));
	matOL[raster.getBegin().getCoords().getX()][raster.getBegin().getCoords().getY()] = true;

	while (!queueOL.empty())
	{
		std::reference_wrapper<Field> Q = queueOL.top();
		queueOL.pop();

		int xQ = Q.get().getCoords().getX();
		int yQ = Q.get().getCoords().getY();

		matOL[xQ][yQ] = false;
		matCL[xQ][yQ] = true;

		if (Q.get() == raster.getEnd())
		{
			raster.setPathFound(true);
			auto execution_time = std::chrono::high_resolution_clock::now() - start;
			auto execution_time_nano = std::chrono::duration_cast<std::chrono::nanoseconds>(execution_time).count();
			std::cout << "Nano: " << execution_time_nano << std::endl;
			break; 
		}

		std::vector<Coords> neighbours;
		if (yQ - 1 >= 0) neighbours.push_back(Coords(xQ, yQ - 1));
		if (yQ + 1 < raster.getN()) neighbours.push_back(Coords(xQ, yQ + 1));
		if (xQ - 1 >= 0) neighbours.push_back(Coords(xQ - 1, yQ));
		if (xQ + 1 < raster.getM()) neighbours.push_back(Coords(xQ + 1, yQ));
		for (Coords ngb : neighbours)
		{
			std::reference_wrapper<Field> ngbField = raster.getField(ngb.getX(), ngb.getY());

			if (matCL[ngb.getX()][ngb.getY()] || !ngbField.get().getAllowed())
				continue;

			if (!matOL[ngb.getX()][ngb.getY()])
			{
				ngbField.get().setParent(&(Q.get()));
				unsigned newG = Q.get().getG() + 1;
				unsigned newH = PathFinder::calculateManhattanH(ngbField.get(), raster.getEnd());
				ngbField.get().updateGHF(newG, newH);
				queueOL.push(ngbField);
				matOL[ngb.getX()][ngb.getY()] = true;
				continue;
			}

			unsigned newG = Q.get().getG() + 1;
			if (newG < ngbField.get().getG())
			{
				ngbField.get().setParent(&(Q.get()));
				ngbField.get().updateGHF(newG);
			}
		}
	}

	for (int idx = 0; idx < raster.getM(); ++idx)
		delete[] matOL[idx];
	delete[] matOL;

	for (int idx = 0; idx < raster.getM(); ++idx)
		delete[] matCL[idx];
	delete[] matCL;
}


/* Dijkstra algorithm */
void PathFinder::Dijkstra_algorithm(Raster& raster) {
	std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

	/* Prepare raster for this algorithm */
	int max = raster.getM() * raster.getN() + 1;
	for (int m_idx = 0; m_idx < raster.getM(); ++m_idx)
	{
		for (int n_idx = 0; n_idx < raster.getN(); ++n_idx)
		{
			raster.getField(m_idx, n_idx).updateGHF(max, 0);
		}
	}
	raster.getBegin().updateGF(0);

	std::vector<std::reference_wrapper<Field> > queue;
	queue.reserve(raster.getM() * raster.getN());
	for (int m_idx = 0; m_idx < raster.getM(); ++m_idx)
	{
		for (int n_idx = 0; n_idx < raster.getN(); ++n_idx)
		{
			queue.push_back(std::ref(raster.getField(m_idx, n_idx)));
		}
	}

	bool** mat = new bool*[raster.getM()];
	for (int idx = 0; idx < raster.getM(); ++idx)
		mat[idx] = new bool[raster.getN()];
	for (int l_idx = 0; l_idx < raster.getM(); ++l_idx)
	{
		for (int c_idx = 0; c_idx < raster.getN(); ++c_idx)
		{
			mat[l_idx][c_idx] = false;
		}
	}

	while(! queue.empty())
	{
		std::reference_wrapper<Field> Q = queue[0];
		int q_idx = 0;
		for (int idx = 1; idx < queue.size(); ++idx)
		{
			if (queue[idx].get().getF() < Q.get().getF())
			{
				Q = queue[idx];
				q_idx = idx;
			}
		}

		std::swap(queue[q_idx], queue[queue.size() - 1]);
		queue.pop_back();

		int xQ = Q.get().getCoords().getX();
		int yQ = Q.get().getCoords().getY();
		mat[xQ][yQ] = true;

		if (!Q.get().getAllowed())
			continue;

		if (Q.get() == raster.getEnd())
		{
			raster.setPathFound(true);
			auto execution_time = std::chrono::high_resolution_clock::now() - start;
			auto execution_time_nano = std::chrono::duration_cast<std::chrono::nanoseconds>(execution_time).count();
			std::cout << "Nano: " << execution_time_nano << std::endl;
			break;
		}

		std::vector<Coords> neighbours;
		if (yQ - 1 >= 0) neighbours.push_back(Coords(xQ, yQ - 1));
		if (yQ + 1 < raster.getN()) neighbours.push_back(Coords(xQ, yQ + 1));
		if (xQ - 1 >= 0) neighbours.push_back(Coords(xQ - 1, yQ));
		if (xQ + 1 < raster.getM()) neighbours.push_back(Coords(xQ + 1, yQ));

		for (Coords ngb : neighbours)
		{
			std::reference_wrapper<Field> ngbField = raster.getField(ngb.getX(), ngb.getY());

			if (mat[ngb.getX()][ngb.getY()] || !ngbField.get().getAllowed())
				continue;

			if (ngbField.get().getF() > Q.get().getF() + 1)
			{
				ngbField.get().updateGF(Q.get().getF() + 1);
				ngbField.get().setParent(&(Q.get()));
			}
		}
	}

	for (int idx = 0; idx < raster.getM(); ++idx)
		delete[] mat[idx];
	delete[] mat;
}


/* Bellman-Ford algorithm */
void PathFinder::Bellman_Ford_algorithm(Raster &raster)
{
	std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

	/* Prepare raster for this algorithm */
	int max = raster.getM() * raster.getN() + 1;
	for (int m_idx = 0; m_idx < raster.getM(); ++m_idx)
	{
		for (int n_idx = 0; n_idx < raster.getN(); ++n_idx)
		{
			raster.getField(m_idx, n_idx).updateGF(max);
		}
	}
	raster.getBegin().updateGF(0);

	bool finish;

	for (int i_idx = 0; i_idx < raster.getN() * raster.getM() - 1; ++i_idx)
	{
		finish = true;

		for (int m_idx = 0; m_idx < raster.getM(); ++m_idx)
		{
			for (int n_idx = 0; n_idx < raster.getN(); ++n_idx)
			{
				std::reference_wrapper<Field> curr_field = raster.getField(m_idx, n_idx);
				if (!curr_field.get().getAllowed())
					continue;

				int xF = raster.getField(m_idx, n_idx).getCoords().getX();
				int yF = raster.getField(m_idx, n_idx).getCoords().getY();

				std::vector<Coords> neighbours;
				if (yF - 1 >= 0) neighbours.push_back(Coords(xF, yF - 1));
				if (yF + 1 < raster.getN()) neighbours.push_back(Coords(xF, yF + 1));
				if (xF - 1 >= 0) neighbours.push_back(Coords(xF - 1, yF));
				if (xF + 1 < raster.getM()) neighbours.push_back(Coords(xF + 1, yF));

				for (Coords ngb : neighbours)
				{
					std::reference_wrapper<Field> ngbField = raster.getField(ngb.getX(), ngb.getY());
					if (!ngbField.get().getAllowed())
						continue;

					if (ngbField.get().getG() > curr_field.get().getG() + 1)
					{
						finish = false;
						ngbField.get().updateGF(curr_field.get().getG() + 1);
						ngbField.get().setParent(&(curr_field.get()));
					}
				}
			}
		}
		if (finish)
			break;
	}

	if (raster.getEnd().getParent() == nullptr)
		return;

	raster.setPathFound(true);
	auto execution_time = std::chrono::high_resolution_clock::now() - start;
	auto execution_time_nano = std::chrono::duration_cast<std::chrono::nanoseconds>(execution_time).count();
	std::cout << "Nano: " << execution_time_nano << std::endl;
}