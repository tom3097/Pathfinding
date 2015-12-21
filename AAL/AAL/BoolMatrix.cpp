#include "BoolMatrix.h"



BoolMatrix::BoolMatrix()
{
}


BoolMatrix::~BoolMatrix()
{
}


bool ** BoolMatrix::createBoolMatrix(unsigned M, unsigned N, bool initVal)
{
	bool** matrix = new bool*[M];
	for (int idx = 0; idx < M; ++idx)
		matrix[idx] = new bool[N];

	for (int r_idx = 0; r_idx < M; ++r_idx)
	{
		for (int c_idx = 0; c_idx < N; ++c_idx)
		{
			matrix[r_idx][c_idx] = initVal;
		}
	}

	return matrix;
}


void BoolMatrix::deleteBoolMatrix(unsigned M, bool ** matrix)
{
	for (int idx = 0; idx < M; ++idx)
		delete[] matrix[idx];
	delete[] matrix;
}
