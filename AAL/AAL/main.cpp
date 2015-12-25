#include <iomanip>
#include "DataGenerator.h"

#define MAX_WIDTH 33
#define MAX_HEIGHT 23


void showAllSolutionsAndTimes(Raster& raster)
{
	long long time;

	bool tiny = raster.getN() <= MAX_WIDTH && raster.getM() <= MAX_HEIGHT;

	if (tiny)
	{
		raster.print();
	}

	time = BellmanFord::findShortestPath(raster, false);
	std::cout << std::left << std::setw(32) << std::setfill(' ') << "Bellman-Ford Algorithm: ";
	std::cout << std::right << std::setw(15) << std::setfill('_') << time << std::endl;
	if (tiny)
	{
		raster.printPath();
	}
	raster.reset();

	time = Dijkstra::findShortestPath_Table(raster, false);
	std::cout << std::left << std::setw(32) << std::setfill(' ') << "Dijkstra Algorithm Table: ";
	std::cout << std::right << std::setw(15) << std::setfill('_') << time << std::endl;
	if (tiny)
	{
		raster.printPath();
	}
	raster.reset();

	time = Dijkstra::findShortestPath_Heap(raster, false);
	std::cout << std::left << std::setw(32) << std::setfill(' ') << "Dijkstra Algorithm Heap: ";
	std::cout << std::right << std::setw(15) << std::setfill('_') << time << std::endl;
	if (tiny)
	{
		raster.printPath();
	}
	raster.reset();

	time = AStar::findShortestPath(raster, false);
	std::cout << std::left << std::setw(32) << std::setfill(' ') << "A Star Algorithm: ";
	std::cout << std::right << std::setw(15) << std::setfill('_') << time << std::endl;
	if (tiny)
	{
		raster.printPath();
	}
	raster.reset();
}


void showStatistics(std::vector<TableLine>& lines)
{
	for (unsigned i_idx = 0; i_idx < lines.size(); ++i_idx)
	{
		std::cout << "n = " << std::right << std::setw(8) << std::setfill('_') << lines[i_idx].get_n() << "\t";
		std::cout << "t(n) = " << std::right << std::setw(15) << std::setfill('_') << lines[i_idx].get_t_n() << "\t";
		std::cout << "T(n) = " << std::right << std::setw(10) << std::setfill('_') << lines[i_idx].get_T_n() << "\t";
		std::cout << "q = " << std::right << std::setw(10) << std::setfill('_') << lines[i_idx].get_q() << "\n";
	}
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
		std::vector<TableLine> lines;

		switch (choice)
		{
		case 1:
			raster = DataGenerator::getFromStandardStream();
			showAllSolutionsAndTimes(raster);
			break;
		case 2:
			raster = DataGenerator::getFromFileStream();
			showAllSolutionsAndTimes(raster);
			break;
		case 3:
			raster = DataGenerator::getRandomParameterized();
			showAllSolutionsAndTimes(raster);
			break;
		case 4:
			lines = DataGenerator::generateStatistics();
			showStatistics(lines);
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

