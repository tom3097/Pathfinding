#include "AStar.h"


AStar::AStar()
{

}


AStar::~AStar()
{

}


unsigned AStar::calculateManhattanH(const Field& from, const Field& to)
{
	return std::abs(from.getCoords().getX() - to.getCoords().getX()) + std::abs(from.getCoords().getY() - to.getCoords().getY());
}


bool AStar::CompareFields::operator() (const Field& field1, const Field& field2)
{
	return field1.getF() > field2.getF();
}


void AStar::prepare(Raster& raster)
{
	for (int m_idx = 0; m_idx < raster.getM(); ++m_idx)
	{
		for (int n_idx = 0; n_idx < raster.getN(); ++n_idx)
		{
			raster.getField(m_idx, n_idx).updateGHF(0, 0);
		}
	}
}


long long AStar::findShortestPath(Raster& raster) {
	long long executionTime = 0;
	Timer timer;

	typedef std::priority_queue<std::reference_wrapper<Field>, std::vector<std::reference_wrapper<Field> >, AStar::CompareFields> Queue;

	AStar::prepare(raster);

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
				unsigned newH = AStar::calculateManhattanH(ngbField.get(), raster.getEnd());
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

	return timer.getEstimatedTime();
}