#include "Raster.h"



Raster::Raster(): M(2), N(2), begin(Coords(0,0)), end(Coords(1,1)), pathFound(false)
{
	matrix.reserve(2);
	std::vector<Field> line(N, Field());

	for (unsigned l_idx = 0; l_idx < M; ++l_idx)
	{
		matrix.push_back(line);
	}

	for (unsigned l_idx = 0; l_idx < M; ++l_idx)
	{
		for (unsigned c_idx = 0; c_idx < N; ++c_idx)
		{
			matrix[l_idx][c_idx].setCoords(Coords(l_idx, c_idx));
		}
	}
}

Raster::Raster(int _M, int _N, bool **_array, Coords _begin, Coords _end) : M(_M), N(_N), begin(_begin), end(_end), pathFound(false)
{
	matrix.reserve(M);
	std::vector<Field> line(N, Field());

	for (unsigned l_idx = 0; l_idx < M; ++l_idx)
	{
		matrix.push_back(line);
	}

	for (unsigned l_idx = 0; l_idx < M; ++l_idx) 
	{
		for (unsigned c_idx = 0; c_idx < N; ++c_idx) 
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
	for (unsigned l_idx = 0; l_idx < M; ++l_idx) 
	{
		for (unsigned c_idx = 0; c_idx < N; ++c_idx)
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


void Raster::print() 
{
	for (unsigned l_idx = 0; l_idx < M; ++l_idx) 
	{
		for (unsigned c_idx = 0; c_idx < N; ++c_idx) 
		{
			if (matrix[l_idx][c_idx] == getBegin()) { std::cout << "1 "; continue; }
			if (matrix[l_idx][c_idx] == getEnd()) { std::cout << "2 "; continue; }
			std::cout << (matrix[l_idx][c_idx].getAllowed() ? ". " : "$ ");
		}
		std::cout << std::endl;
	}
}


void Raster::printPath() 
{
	if (!pathFound)
		return;

	int** map = MyMatrix<int>::createMatrix(M, N, 0);

	Field *f = &getEnd();
	while (*f != getBegin()) 
	{
		map[f->getCoords().getX()][f->getCoords().getY()] = 1;
		f = f->getParent();
	}

	map[getBegin().getCoords().getX()][getBegin().getCoords().getY()] = 2;
	map[getEnd().getCoords().getX()][getEnd().getCoords().getY()] = 2;

	for (unsigned l_idx = 0; l_idx < M; ++l_idx) 
	{
		for (unsigned c_idx = 0; c_idx < N; ++c_idx) 
		{
			if (map[l_idx][c_idx] == 2) { std::cout << "@ "; continue; }
			if (map[l_idx][c_idx] == 1) { std::cout << "# "; continue; }
			std::cout << ". ";
		}
		std::cout << std::endl;
	}

	MyMatrix<int>::deleteMatrix(M, map);
}