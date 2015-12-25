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


unsigned AStar::calculateNothing(const Field& from, const Field& to)
{
	return 0;
}


bool AStar::CompareFields::operator() (const Field& field1, const Field& field2)
{
	return field1.getF() > field2.getF();
}


void AStar::prepare(Raster& raster)
{
	for (unsigned m_idx = 0; m_idx < raster.getM(); ++m_idx)
	{
		for (unsigned n_idx = 0; n_idx < raster.getN(); ++n_idx)
		{
			raster.getField(m_idx, n_idx).updateGHF(0, 0);
		}
	}
}


long long AStar::findShortestPath(Raster& raster, bool timeComplexVerif) 
{
	long long executionTime = 0;
	Timer timer;

	typedef std::priority_queue<std::reference_wrapper<Field>, std::vector<std::reference_wrapper<Field> >, AStar::CompareFields> Queue;

	AStar::prepare(raster);

	bool** matOL = MyMatrix<bool>::createMatrix(raster.getM(), raster.getN(), false);
	bool** matCL = MyMatrix<bool>::createMatrix(raster.getM(), raster.getN(), false);

	Queue queueOL;

	queueOL.push(std::ref(raster.getBegin()));
	matOL[raster.getBegin().getCoords().getX()][raster.getBegin().getCoords().getY()] = true;

	std::function<unsigned(Field&, Field&)> heuristicFunction = calculateManhattanH;
	if (timeComplexVerif)
		heuristicFunction = calculateNothing;

	while (!queueOL.empty())
	{
		std::reference_wrapper<Field> Q = queueOL.top();
		queueOL.pop();

		int xQ = Q.get().getCoords().getX();
		int yQ = Q.get().getCoords().getY();

		if (matCL[xQ][yQ] == true)
			continue;

		matOL[xQ][yQ] = false;
		matCL[xQ][yQ] = true;

		if (Q.get() == raster.getEnd())
		{
			raster.setPathFound(true);
			if (!timeComplexVerif)
				break;
		}

		std::vector<Coords> neighbours;
		if (yQ - 1 >= 0) neighbours.push_back(Coords(xQ, yQ - 1));
		if (yQ + 1 < (int)raster.getN()) neighbours.push_back(Coords(xQ, yQ + 1));
		if (xQ - 1 >= 0) neighbours.push_back(Coords(xQ - 1, yQ));
		if (xQ + 1 < (int)raster.getM()) neighbours.push_back(Coords(xQ + 1, yQ));
		for (Coords ngb : neighbours)
		{
			std::reference_wrapper<Field> ngbField = raster.getField(ngb.getX(), ngb.getY());

			if (matCL[ngb.getX()][ngb.getY()] || !ngbField.get().getAllowed())
				continue;

			if (!matOL[ngb.getX()][ngb.getY()])
			{
				ngbField.get().setParent(&(Q.get()));
				int newG = Q.get().getG() + 1;
				int newH = heuristicFunction(ngbField.get(), raster.getEnd());
				ngbField.get().updateGHF(newG, newH);
				queueOL.push(ngbField);
				matOL[ngb.getX()][ngb.getY()] = true;
				continue;
			}

			int newG = Q.get().getG() + 1;
			if (newG < ngbField.get().getG())
			{
				ngbField.get().setParent(&(Q.get()));
				ngbField.get().updateGHF(newG);
				queueOL.push(ngbField);
			}
		}
	}

	MyMatrix<bool>::deleteMatrix(raster.getM(), matOL);
	MyMatrix<bool>::deleteMatrix(raster.getM(), matCL);

	return timer.getEstimatedTime();
}