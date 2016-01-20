#pragma once

#include "Field.h"
#include "MyMatrix.h"
#include <vector>
#include <iostream>


/* Class representing raster */
class Raster {
	typedef std::vector<std::vector<Field> > Matrix;

	/* Number of rows */
	unsigned M;

	/* Number of columns */
	unsigned N;

	/* Matrix */
	Matrix matrix;

	/* Start field coordinations */
	Coords begin;

	/* End field coordinations */
	Coords end;

	/* Informs if path has been found */
	bool pathFound ;
public:
	Raster();
	Raster(unsigned _M, unsigned _N, bool **_array, Coords _begin, Coords _end);
	~Raster();

	/* Reset all fields in matrix */
	void reset();

	/* Set pathFound
	 * @param {bool} val: new pathFound value
	 */
	void setPathFound(bool val);

	/* Get pathFound
	 * @returns {bool}: pathFound value
	 */
	bool getPathFound();

	/* Get field from matrix
	 * @param {int} _x: x coordiante
	 * @param {int} _y: y coordinate
	 * @returns {Field&}: proper field
	 */
	Field& getField(int _x, int _y);

	/* Get start field
	 * @returns {Field&}: begin field
	 */
	Field& getBegin();

	/* Get end field
	* @returns {Field&}: end field
	*/
	Field& getEnd();

	/* Get number of rows
	 * @returns {unsigned}: number of rows
	 */
	unsigned getM();

	/* Get number of columns
	* @returns {unsigned}: number of columns
	*/
	unsigned getN();

	/* Print map without path */
	void print();

	/* Print map with path*/
	void printPath();
};

