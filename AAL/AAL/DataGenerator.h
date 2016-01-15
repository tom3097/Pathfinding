#pragma once

#include "Raster.h"
#include "MyMatrix.h"
#include "BellmanFord.h"
#include "Dijkstra.h"
#include "AStar.h"
#include "TableLine.h"
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cmath>

class DataGenerator
{
public:
	enum Algorithm
	{
		BELLMAN_FORD = 1, DIJKSTRA_TABLE, DIJKSTRA_HEAP, A_STAR,
	};

	enum FieldType
	{
		NOTHING = '0', BEGIN = '1', END = '2', WHITE = '.', BLACK = '$',
	};
private:
	DataGenerator();
	~DataGenerator();

	/* Create raster from vector with proper data
	 * @param {std::vector<std::string>} lines: vector with string lines
	 * @returns {Raster}: created raster
	 */
	static Raster createFromVector(std::vector<std::string>& lines);

	/* Create parameterized random raster
	 * @param {unsigned} M: number of rows
	 * @param {unsigned} N: number of columns
	 * @param {double} probability: probability of color white
	 * @returns {Raster}: created raster
	 */
	static Raster createRandomParameterized(unsigned M, unsigned N, double probability);

	/* Calculate average time for chosen algorithm
	 * @param {unsigned} M: number of rows
	 * @param {unsigned} N: number of columns
	 * @param {Algorithm} algorithm
	 * @returns {long long}: measured time
	 */
	static long long getAlgorithmAverageTime(unsigned M, unsigned N, Algorithm algorithm);

	/* Calculate theoretical time for algorithm with O(n^2)
	 * @param {unsigned} M: number of rows
	 * @param {unsigned} N: number of columns
	 * @returns {long long}: theoretical execution time
	 */
	static long long calculateTimeNN(unsigned M, unsigned N);

	/* Calculate theoretical time for algorithm with O(n*log(n))
	* @param {unsigned} M: number of rows
	* @param {unsigned} N: number of columns
	* @returns {long long}: theoretical execution time
	*/
	static long long calculateTimeNLogN(unsigned M, unsigned N);
public:
	/* Create raster from data from file
	 * @returns {Raster}: created raster
	 */
	static Raster getFromFileStream();

	/* Create raster from data from file
	 * @param {std::string} path: path to file
	 * @returns {Raster}: created raster
	 */
	static Raster getFromFileStream(std::string path);

	/* Create raster from data from standard input stream
	 * @returns {Raster}: created raster
	 */
	static Raster getFromStandardStream();

	/* Create parameterized random raster
	 * @returns {Raster}: created raster
	 */
	static Raster getRandomParameterized();

	/* Create parameterized random raster
	 * @param {unsigned}: M
	 * @param {unsigned} N: number of columns
	 * @param {double} probability: probability of white field
	 * @returns {Raster}: created raster
	 */
	static Raster getRandomParameterized(unsigned M, unsigned N, double probability);

	/* Generate statistic for chosen algorithm
	 * @returns {std::vector<TableLine>}: vector with basic statistic informations for each iteration
	 */
	static std::vector<TableLine> generateStatistics();

	/* Generate statistic for chosen algorithm
	 * @param {Algorithm} algorithm: chosen algorithm
	 * @param {unsigned} M: initial number of rows
	 * @param {unsigned} N: initial number of columns
	 * @param {unsigned} step: number to be added to columns and rows when increasing dimensions
	 * @returns {std::vector<TableLine>}: vector with basic statistic informations for each iteration
	 */
	static std::vector<TableLine> generateStatistics(Algorithm algorithm, unsigned M, unsigned N, unsigned step);
};

