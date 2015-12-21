#include "DataGenerator.h"
#include "AStar.h"
#include "BellmanFord.h"
#include "Dijkstra.h"
#include <string>
#include <fstream>


void showAllPathsAndTimes(Raster& raster)
{
	long long time;
	raster.printMap();

	time = BellmanFord::findShortestPath(raster);
	std::cout << "Bellman-Ford Algorithm" << std::endl;
	std::cout << "Time (nano): " << time << std::endl;
	std::cout << "Path: " << std::endl;
	raster.printWayMap();

	raster.reset();

	time = Dijkstra::findShortestPath(raster);
	std::cout << "Dijkstra Algorithm" << std::endl;
	std::cout << "Time (nano): " << time << std::endl;
	std::cout << "Path: " << std::endl;
	raster.printWayMap();

	raster.reset();

	time = AStar::findShortestPath(raster);
	std::cout << "A Star Algorithm" << std::endl;
	std::cout << "Time (nano): " << time << std::endl;
	std::cout << "Path: " << std::endl;
	raster.printWayMap();
}


void startProgram()
{
	std::cout << "This program is used to find the shostest path between two different white fields.\n"
		<< "Path contains of only white fields (doesnt have black fields).\n";

	while (true)
	{
		int choice;

		std::cout << "Choose option:\n1(testing corectness) - get raster from standard input stream\n"
			<< "2(testing corectness) - get raster from file\n"
			<< "3(testing corectness) - generate random raster with parametrization\n"
			<< "4(results presentation) - generate random raster and present the results\n"
			<< "5 - close program\n";

		std::cin >> choice;

		Raster raster;

		switch (choice)
		{
		case 1:
			raster = DataGenerator::getFromStandardStream();
			showAllPathsAndTimes(raster);
			break;
		case 2:
			raster = DataGenerator::getFromFileStream();
			showAllPathsAndTimes(raster);
			break;
		case 3:
			/* rodo */
			break;
		case 4:
			/* todo*/
			break;
		case 5:
			exit(0);
		}
	}
}


int main() 
{	
	startProgram();
	return 0;
}

