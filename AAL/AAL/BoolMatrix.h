#pragma once

class BoolMatrix
{
private:
	BoolMatrix();
	~BoolMatrix();
public:
	/* Create matrix of bool values
	 * @param {unsigned} M: number of rows
	 * @param {unsigned} N: number of columns
	 * @param {bool} initVal: initial value for matrix
	 * @returns {bool **}: matrix of bool values
	 */
	static bool ** createBoolMatrix(unsigned M, unsigned N, bool initVal);

	/* Delete matrix of bool values
	 * @param {unsigned} M: number of rows
	 * @param {bool **} matrix: matrix to delete
	 */
	static void deleteBoolMatrix(unsigned M, bool ** matrix);
};

