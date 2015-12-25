#pragma once

template< class T >
class MyMatrix
{
private:
	MyMatrix() {};
	~MyMatrix() {};
public:
	/* Create matrix of T values
	* @param {unsigned} M: number of rows
	* @param {unsigned} N: number of columns
	* @param {bool} initVal: initial value for matrix
	* @returns {bool **}: matrix of T values
	*/
	static T ** createMatrix(unsigned M, unsigned N, T initVal)
	{
		T** matrix = new T*[M];
		for (unsigned idx = 0; idx < M; ++idx)
			matrix[idx] = new T[N];

		for (unsigned r_idx = 0; r_idx < M; ++r_idx)
		{
			for (unsigned c_idx = 0; c_idx < N; ++c_idx)
			{
				matrix[r_idx][c_idx] = initVal;
			}
		}

		return matrix;
	}

	/* Delete matrix of T values
	* @param {unsigned} M: number of rows
	* @param {bool **} matrix: matrix to delete
	*/
	static void deleteMatrix(unsigned M, T ** matrix)
	{
		for (unsigned idx = 0; idx < M; ++idx)
			delete[] matrix[idx];
		delete[] matrix;
	}
};