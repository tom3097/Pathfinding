#pragma once

#include "Raster.h"
#include <queue>
#include <algorithm>
#include <chrono>

class PathFinder
{
public:
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

	static void A_star_algorithm(Raster& raster);
	static void Dijkstra_algorithm(Raster& raster);
	static void Bellman_Ford_algorithm(Raster& raster);
private:
	PathFinder();
	~PathFinder();
};

