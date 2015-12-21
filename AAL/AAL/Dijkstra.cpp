#include "Dijkstra.h"



Dijkstra::Dijkstra()
{
}


Dijkstra::~Dijkstra()
{
}


void Dijkstra::prepare(Raster& raster)
{
	int max = raster.getM() * raster.getN() + 1;
	for (int m_idx = 0; m_idx < raster.getM(); ++m_idx)
	{
		for (int n_idx = 0; n_idx < raster.getN(); ++n_idx)
		{
			raster.getField(m_idx, n_idx).updateGHF(max, 0);
		}
	}
	raster.getBegin().updateGF(0);
}


long long Dijkstra::findShortestPath(Raster& raster) {
	Timer timer;

	Dijkstra::prepare(raster);

	std::vector<std::reference_wrapper<Field> > queue;
	queue.reserve(raster.getM() * raster.getN());
	for (int m_idx = 0; m_idx < raster.getM(); ++m_idx)
	{
		for (int n_idx = 0; n_idx < raster.getN(); ++n_idx)
		{
			queue.push_back(std::ref(raster.getField(m_idx, n_idx)));
		}
	}

	bool** mat = BoolMatrix::createBoolMatrix(raster.getM(), raster.getN(), false);

	while (!queue.empty())
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

	BoolMatrix::deleteBoolMatrix(raster.getM(), mat);

	return timer.getEstimatedTime();
}