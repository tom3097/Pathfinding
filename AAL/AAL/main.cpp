#include "AStar.h"
#include "BellmanFord.h"
#include "Dijkstra.h"
#include <string>
#include <fstream>

bool ** get2Darray(size_t M, size_t N) 
{
	bool** arr = new bool*[M];
	for (int l_idx = 0; l_idx < M; ++l_idx)
		arr[l_idx] = new bool[N];

	for (int l_idx = 0; l_idx < M; ++l_idx)
		for (int c_idx = 0; c_idx < N; ++c_idx)
			arr[l_idx][c_idx] = true;

	return arr;
}


void deleteArray2D(bool **arrayToDelete, size_t M)
{
	for (int idx = 0; idx < M; ++idx)
		delete[] arrayToDelete[idx];
	delete[] arrayToDelete;
}


void getFromInputStream()
{
	int choice;

	std::cout << "Getting raster from input stream.\n"
		<< "1 - get from standard input stream (keyboard)\n"
		<< "2 - get from file\n"
		<< "3 - back to main menu\n";

	std::cin >> choice;

	switch (choice)
	{
	case 1:
		/* todo */
		break;
	case 2:
		/* todo */
		break;
	case 3: 
		break;
	}
}


void startProgram()
{
	std::cout << "This program is used to find the shostest path between two different white fields.\n"
		<< "Path contains of only white fields (doesnt have black fields).\n";

	while (true)
	{
		int choice;

		std::cout << "Choose option:\n1(testing corectness) - get raster from input stream\n"
			<< "2(testing corectness) - generate random raster with parametrization\n"
			<< "3(results presentation) - generate random raster and present the results\n"
			<< "4 - close program\n";

		std::cin >> choice;

		switch (choice)
		{
		case 1:
			getFromInputStream();
			break;
		case 2:
			/* todo */
			break;
		case 3:
			/* rodo */
			break;
		case 4:
			exit(0);
		}
	}
}


int main() 
{	

	//std::cout << std::clock() << std::endl;
	//startProgram();
	size_t M = 100;
	size_t N = 100;

	//while (true)
	//{
	//	std::cout << clock() << std::endl;
	//	std::cout << std::clock() << std::endl;
	//}

	bool ** bTable = get2Darray(M, N);

	/* Zabronione punkty */
	bTable[3][0] = bTable[3][1] = bTable[3][2] = bTable[3][3] = bTable[3][4] = bTable[3][5] = bTable[3][1] = false;
	bTable[1][3] = bTable[2][3] = false;

	Raster raster(M, N, bTable, Coords(1, 2), Coords(1,20));
	//raster.printMap();

	std::cout << "Bellman_Ford\n";
	std::cout << BellmanFord::findShortestPath(raster) << std::endl;
	//raster.printWayMap();

	raster.reset();
	std::cout << "A_star\n";
	std::cout << AStar::findShortestPath(raster) << std::endl;
	//raster.printWayMap();

	raster.reset();
	std::cout << "Dijkstra\n";
	std::cout << Dijkstra::findShortestPath(raster) << std::endl;
	//raster.printWayMap();

	//std::cout << std::clock() << std::endl;

	return 0;
}

