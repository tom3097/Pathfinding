#pragma once

#include "Raster.h"
#include "BoolMatrix.h"
#include <string>
#include <iostream>
#include <fstream>

class DataGenerator
{
private:
	DataGenerator();
	~DataGenerator();

	/* Begin white field id */
	static const char BEGIN = '1';
	/* End white field id */
	static const char END = '2';
	/* White field id */
	static const char WHITE = 'W';
	/* Black field id */
	static const char BLACK = 'B';

	/* Create raster from vector with proper data
	 * @param {std::vector<std::string>} lines: vector with string lines
	 * @returns {Raster}: created raster
	 */
	static Raster createFromVector(std::vector<std::string>& lines);
public:
	/* Get data from file to create raster 
	 * @returns {Raster}: created raster
	 */
	static Raster getFromFileStream();

	/* Get data from standard stream to create raster
	 * @returns {Raster}: created raster
	 */
	static Raster getFromStandardStream();

	/* Get parameterized random raster
	 * @returns {Raster}: created raster
	 */
	static Raster getRandomParameterized();

	/* Get random raster 
	 * @returns {Raster}: created raster
	 */
	static Raster getRandom();
};

