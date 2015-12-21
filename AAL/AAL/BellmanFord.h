#pragma once

#include "Raster.h"
#include "Timer.h"
#include <functional>

class BellmanFord
{
private:
	BellmanFord();
	~BellmanFord();

	/* Prepare raster to Bellman Ford algorithm (set proper values of G, H, F)
	* @param {Raster&} raster: data to modify
	*/
	static void prepare(Raster& raster);
public:
	/* Find the shortest path using Bellman Ford algorithm
	* @param {Raster&} raster: data to find path and modify
	* @returns {long long}: measured time
	*/
	static long long findShortestPath(Raster& raster);
};

