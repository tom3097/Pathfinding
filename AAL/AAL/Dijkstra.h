#pragma once

#include "Raster.h"
#include "Timer.h"
#include "MyMatrix.h"
#include "Heap.h"
#include <functional>

class Dijkstra
{
private:
	Dijkstra();
	~Dijkstra();

	/* Prepare raster to Dijkstra algorithm (set proper values of G, H, F)
	 * @param {Raster&} raster: data to modify
	 */
	static void prepare(Raster& raster);
public:
	/* Find the shortest path using Dijkstra algorithm
	 * where queue is implemented with array
	 * @param {Raster&} raster: data to find path and modify
	 * @param {bool} timeComplexVerif: true if we want to verify time complexity
	 * @returns {long long}: measured time
	 */
	static long long findShortestPath_Table(Raster& raster, bool timeComplexVerif);

	/* Find the shortest path using Dijkstra algorithm
	* where queue is implemented with min heap
	* @param {Raster&} raster: data to find path and modify
	* @param {bool} timeComplexVerif: true if we want to verify time complexity
	* @returns {long long}: measured time
	*/
	static long long findShortestPath_Heap(Raster& raster, bool timeComplexVerif);
};

