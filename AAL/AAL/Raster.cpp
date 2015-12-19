#include "Raster.h"


Raster::Raster(int _M, int _N, bool **_array, Coords _begin, Coords _end) : M(_M), N(_N), begin(_begin), end(_end), pathFound(false)
{
	matrix.reserve(M);
	std::vector<Field> line(N, Field());

	for (int l_idx = 0; l_idx < M; ++l_idx)
	{
		matrix.push_back(line);
	}

	for (int l_idx = 0; l_idx < M; ++l_idx) 
	{
		for (int c_idx = 0; c_idx < N; ++c_idx) 
		{
			if (!_array[l_idx][c_idx])
				matrix[l_idx][c_idx].setAllowed(false);
			matrix[l_idx][c_idx].setCoords(Coords(l_idx, c_idx));
		}
	}
}


Raster::~Raster()
{

}


void Raster::reset() 
{
	for (int l_idx = 0; l_idx < M; ++l_idx) 
	{
		for (int c_idx = 0; c_idx < N; ++c_idx)
		{
			matrix[l_idx][c_idx].reset();
		}
	}
}


bool Raster::getPathFound()
{
	return pathFound;
}


void Raster::setPathFound(bool val)
{
	pathFound = val;
}


Field& Raster::getField(int _x, int _y) 
{ 
	return matrix[_x][_y]; 
}


Field& Raster::getBegin() 
{ 
	return matrix[begin.getX()][begin.getY()]; 
}


Field& Raster::getEnd() 
{ 
	return matrix[end.getX()][end.getY()]; 
}


size_t Raster::getM() 
{ 
	return M;
}


size_t Raster::getN() 
{ 
	return N; 
}


void Raster::printMap() 
{
	for (int l_idx = 0; l_idx < M; ++l_idx) 
	{
		for (int c_idx = 0; c_idx < N; ++c_idx) 
		{
			if (matrix[l_idx][c_idx] == getBegin()) { std::cout << "1 "; continue; }
			if (matrix[l_idx][c_idx] == getEnd()) { std::cout << "2 "; continue; }
			std::cout << (matrix[l_idx][c_idx].getAllowed() ? "W " : "B ");
		}
		std::cout << std::endl;
	}
}


void Raster::printWayMap() 
{
	if (!pathFound)
		return;

	int** wayMap = new int*[M];
	for (int idx = 0; idx < M; ++idx)
		wayMap[idx] = new int[N];

	for (int l_idx = 0; l_idx < M; ++l_idx)
		for (int c_idx = 0; c_idx < N; ++c_idx)
			wayMap[l_idx][c_idx] = 0;

	Field *f = &getEnd();
	while (*f != getBegin()) 
	{
		wayMap[f->getCoords().getX()][f->getCoords().getY()] = 1;
		f = f->getParent();
	}

	wayMap[getBegin().getCoords().getX()][getBegin().getCoords().getY()] = 2;
	wayMap[getEnd().getCoords().getX()][getEnd().getCoords().getY()] = 2;

	for (int l_idx = 0; l_idx < M; ++l_idx) 
	{
		for (int c_idx = 0; c_idx < N; ++c_idx) 
		{
			if (wayMap[l_idx][c_idx] == 2) { std::cout << "@ "; continue; }
			if (wayMap[l_idx][c_idx] == 1) { std::cout << "# "; continue; }
			std::cout << ". ";
		}
		std::cout << std::endl;
	}

	for (int idx = 0; idx < M; ++idx)
		delete[] wayMap[idx];
	delete[] wayMap;
}