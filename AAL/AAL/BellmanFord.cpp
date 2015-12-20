#include "BellmanFord.h"


BellmanFord::BellmanFord()
{

}


BellmanFord::~BellmanFord()
{

}


void BellmanFord::prepare(Raster& raster)
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


long long BellmanFord::findShortestPath(Raster &raster)
{
	Timer timer;
	long long executionTime = 0;

	BellmanFord::prepare(raster);

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

					if (ngbField.get().getF() > curr_field.get().getF() + 1)
					{
						finish = false;
						ngbField.get().updateGF(curr_field.get().getF() + 1);
						ngbField.get().setParent(&(curr_field.get()));
					}
				}
			}
		}
		if (finish)
			break;
	}

	if (raster.getEnd().getParent() != nullptr)
	{
		raster.setPathFound(true);
	}

	return timer.getEstimatedTime();
}