#include <iomanip>
#include "DataGenerator.h"
#include <cstdlib>

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


void info()
{
	std::cout << "\n\nUsage:\n\n:"
		<< "If you want to read data from file:\n"
		<< "[-a/-dt/-dh/-bf] -f path\n\n"
		<< "If you want to generate parameterized data:\n"
		<< "[-a/-dt/-dh/-b] -g M N probability\n\n"
		<< "If you want to get statistics:\n"
		<< "[-a/-dt/-dh/-b] -s M N step \n\n"
		<< "where -a: A* -dt: DijkstraTable -dh: DijkstraHeap -bf: Bellman-Ford\n\n";
}




int main(int argc, char **argv) 
{	
	/* Przypadek uruchamiania bez wybranej opcji */
	if(argc == 1)
		startProgram();

	/* Przypadek wczytywania z pliku */
	if (argc == 4)
	{
		std::string option_1(argv[1]);
		std::string option_2(argv[2]);
		std::string option_3(argv[3]);
		if (option_2 == "-f")
		{
			Raster raster = DataGenerator::getFromFileStream(option_3);
			if (option_1 == "-a")
			{
				long long time = AStar::findShortestPath(raster, false);
				std::cout << std::left << std::setw(32) << std::setfill(' ') << "A Star Algorithm: ";
				std::cout << std::right << std::setw(15) << std::setfill('_') << time << std::endl;
				raster.print();
				std::cout << std::endl;
				raster.printPath();
				exit(0);
			}
			else if (option_1 == "-dh")
			{
				long long time = Dijkstra::findShortestPath_Heap(raster, false);
				std::cout << std::left << std::setw(32) << std::setfill(' ') << "Dijkstra Algorithm Heap: ";
				std::cout << std::right << std::setw(15) << std::setfill('_') << time << std::endl;
				raster.print();
				std::cout << std::endl;
				raster.printPath();
				exit(0);
			}
			else if (option_1 == "-dt")
			{
				long long time = Dijkstra::findShortestPath_Table(raster, false);
				std::cout << std::left << std::setw(32) << std::setfill(' ') << "Dijkstra Algorithm Table: ";
				std::cout << std::right << std::setw(15) << std::setfill('_') << time << std::endl;
				raster.print();
				std::cout << std::endl;
				raster.printPath();
				exit(0);
			}
			else if (option_1 == "-bf")
			{
				long long time = BellmanFord::findShortestPath(raster, false);
				std::cout << std::left << std::setw(32) << std::setfill(' ') << "Bellman-Ford Algorithm: ";
				std::cout << std::right << std::setw(15) << std::setfill('_') << time << std::endl;
				raster.print();
				std::cout << std::endl;
				raster.printPath();
				exit(0);
			}
			else
			{
				info();
				exit(-1);
			}
		}
		else
		{
			info();
			exit(-1);
		}
	}

	/* Przypadek generowania losowego parametryzowanego rastra */
	if (argc == 6 && std::string(argv[2]) == "-g")
	{
		std::string option_1(argv[1]);
		std::string option_3(argv[3]);
		std::string option_4(argv[4]);
		std::string option_5(argv[5]);

		unsigned M;
		unsigned N;
		double probability;

		try
		{
			M = (unsigned)std::stoi(option_3);
			N = (unsigned)std::stoi(option_4);
			probability = std::stod(option_5);
		}
		catch (...)
		{
			info();
			exit(-1);
		}

		Raster raster = DataGenerator::getRandomParameterized(M, N, probability);
		if (option_1 == "-a")
		{
			long long time = AStar::findShortestPath(raster, false);
			std::cout << std::left << std::setw(32) << std::setfill(' ') << "A Star Algorithm: ";
			std::cout << std::right << std::setw(15) << std::setfill('_') << time << std::endl;
			raster.print();
			std::cout << std::endl;
			raster.printPath();
			exit(0);
		}
		else if (option_1 == "-dh")
		{
			long long time = Dijkstra::findShortestPath_Heap(raster, false);
			std::cout << std::left << std::setw(32) << std::setfill(' ') << "Dijkstra Algorithm Heap: ";
			std::cout << std::right << std::setw(15) << std::setfill('_') << time << std::endl;
			raster.print();
			std::cout << std::endl;
			raster.printPath();
			exit(0);
		}
		else if (option_1 == "-dt")
		{
			long long time = Dijkstra::findShortestPath_Table(raster, false);
			std::cout << std::left << std::setw(32) << std::setfill(' ') << "Dijkstra Algorithm Table: ";
			std::cout << std::right << std::setw(15) << std::setfill('_') << time << std::endl;
			raster.print();
			std::cout << std::endl;
			raster.printPath();
			exit(0);
		}
		else if (option_1 == "-bf")
		{
			long long time = BellmanFord::findShortestPath(raster, false);
			std::cout << std::left << std::setw(32) << std::setfill(' ') << "Bellman-Ford Algorithm: ";
			std::cout << std::right << std::setw(15) << std::setfill('_') << time << std::endl;
			raster.print();
			std::cout << std::endl;
			raster.printPath();
			exit(0);
		}
		else
		{
			info();
			exit(-1);
		}
	}

	/* Przypadek generowania tabelki z czasami wykonania */
	if (argc == 6 && std::string(argv[2]) == "-t")
	{
		std::string option_1(argv[1]);
		std::string option_3(argv[3]);
		std::string option_4(argv[4]);
		std::string option_5(argv[5]);

		unsigned M;
		unsigned N;
		unsigned step;

		try
		{
			M = (unsigned)std::stoi(option_3);
			N = (unsigned)std::stoi(option_4);
			step = (unsigned)std::stod(option_5);
		}
		catch (...)
		{
			info();
			exit(-1);
		}

		if (option_1 == "-a")
		{
			std::vector<TableLine> lines = DataGenerator::generateStatistics(DataGenerator::Algorithm::A_STAR, M, N, step);
			showStatistics(lines);
			std::cout << std::endl;
			exit(0);
		}
		else if (option_1 == "-dh")
		{
			std::vector<TableLine> lines = DataGenerator::generateStatistics(DataGenerator::Algorithm::DIJKSTRA_HEAP, M, N, step);
			showStatistics(lines);
			std::cout << std::endl;
			exit(0);
		}
		else if (option_1 == "-dt")
		{
			std::vector<TableLine> lines = DataGenerator::generateStatistics(DataGenerator::Algorithm::DIJKSTRA_TABLE, M, N, step);
			showStatistics(lines);
			std::cout << std::endl;
			exit(0);
		}
		else if (option_1 == "-bf")
		{
			std::vector<TableLine> lines = DataGenerator::generateStatistics(DataGenerator::Algorithm::BELLMAN_FORD, M, N, step);
			showStatistics(lines);
			std::cout << std::endl;
			exit(0);
		}
		else
		{
			info();
			exit(-1);
		}
	}

	info();
	exit(-1);

	return 0;
}

