#pragma once

#include "Field.h"
#include <vector>
#include <iostream>


/* Class representing raster */
class Raster {
	typedef std::vector<std::vector<Field> > Matrix;

	/* Number of rows */
	size_t M;

	/* Number of columns */
	size_t N;

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
	Raster(int _M, int _N, bool **_array, Coords _begin, Coords _end);
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
	 * @returns {size_t}: number of rows
	 */
	size_t getM();

	/* Get number of columns
	* @returns {size_t}: number of columns
	*/
	size_t getN();

	/* Print map without path */
	void printMap();

	/* Print map with path*/
	void printWayMap();
};

