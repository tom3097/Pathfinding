#pragma once

#include "Raster.h"
#include "Timer.h"
#include <functional>

class Dijkstra
{
private:
	Dijkstra();
	~Dijkstra();
public:
	/* Prepare raster to Dijkstra algorithm (set proper values of G, H, F)
	* @param {Raster&} raster: data to modify
	*/
	static void prepare(Raster& raster);

	/* Find the shortest path using Dijkstra algorithm
	* @param {Raster&} raster: data to find path and modify
	* @returns {long long}: measured time
	*/
	static long long findShortestPath(Raster& raster);
};

