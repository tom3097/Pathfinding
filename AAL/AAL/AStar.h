#pragma once

#include "Raster.h"
#include "Timer.h"
#include "BoolMatrix.h"
#include <queue>
#include <functional>

class AStar
{
private:
	AStar();
	~AStar();

	/* Heuristic function that estimates the length from one field to another. It has a property of underestimation
	* so that's why with this function we can find optimal path
	* @param {Field&}: begin field
	* @param {Field&}: end field
	* @returns {Field&}: calculated estimated length between them
	*/
	unsigned static calculateManhattanH(const Field& from, const Field& to);

	/* Class with overloaded operator() used by priority queue */
	class CompareFields
	{
	public:
		bool operator() (const Field& field1, const Field& field2);
	};

	/* Prepare raster to A star algorithm (set proper values of G, H, F)
	* @param {Raster&} raster: data to modify
	*/
	static void prepare(Raster& raster);
public:
	/* Find the shortest path using A star algorithm 
	 * @param {Raster&} raster: data to find path and modify
	 * @returns {long long}: measured time
	 */
	static long long findShortestPath(Raster& raster);
};

