#include "DataGenerator.h"



DataGenerator::DataGenerator()
{
}


DataGenerator::~DataGenerator()
{
}


Raster DataGenerator::createFromVector(std::vector<std::string>& lines)
{
	if (lines.empty())
	{
		return Raster();
	}

	unsigned M = lines.size();
	unsigned N = lines[0].length();

	bool beginSet = false;
	Coords begin;
	bool endSet = false;
	Coords end;

	bool ** matrix = MyMatrix<bool>::createMatrix(M, N, false);

	for (unsigned l_idx = 0; l_idx < M; ++l_idx)
	{
		for (unsigned c_idx = 0; c_idx < N; ++c_idx)
		{
			if (lines[l_idx][c_idx] == BEGIN)
			{
				if (beginSet)
				{
					MyMatrix<bool>::deleteMatrix(M, matrix);
					return Raster();
				}

				beginSet = true;
				begin.setXY(l_idx, c_idx);

				matrix[l_idx][c_idx] = true;
			}
			else if (lines[l_idx][c_idx] == END)
			{
				if (endSet)
				{
					MyMatrix<bool>::deleteMatrix(M, matrix);
					return Raster();
				}

				endSet = true;
				end.setXY(l_idx, c_idx);

				matrix[l_idx][c_idx] = true;
			}
			else if (lines[l_idx][c_idx] == WHITE)
			{
				matrix[l_idx][c_idx] = true;
			}
			else if (lines[l_idx][c_idx] == BLACK)
			{
				continue;
			}
			else
			{
				MyMatrix<bool>::deleteMatrix(M, matrix);
				return Raster();
			}
		}
	}

	if (!beginSet || !endSet)
	{
		MyMatrix<bool>::deleteMatrix(M, matrix);
		return Raster();
	}

	Raster raster(M, N, matrix, begin, end);
	MyMatrix<bool>::deleteMatrix(M, matrix);
	return raster;
}


Raster DataGenerator::createRandomParameterized(unsigned M, unsigned N, double probability)
{
	bool preparing = true;

	unsigned numberWhite = (unsigned)(M * N * probability);
	if (numberWhite < 2)
		return Raster();

	unsigned currNumberWhite = 0;

	bool ** matrix = MyMatrix<bool>::createMatrix(M, N, false);
	char ** helper = MyMatrix<char>::createMatrix(M, N, NOTHING);

	std::vector<Coords> queue;
	std::vector<Coords> whiteCollection;

	srand(unsigned(time(nullptr)));

	Coords firstWhite(rand() % M, rand() % N);
	queue.push_back(firstWhite);
	whiteCollection.push_back(firstWhite);

	matrix[firstWhite.getX()][firstWhite.getY()] = true;

	helper[firstWhite.getX()][firstWhite.getY()] = WHITE;
	++currNumberWhite;

	while (preparing)
	{
		unsigned idx = rand() % queue.size();
		Coords chosen = queue[idx];
		std::swap(queue[idx], queue[queue.size() - 1]);
		queue.pop_back();

		int xChosen = chosen.getX();
		int yChosen = chosen.getY();

		std::vector<Coords> neighbours;
		if (yChosen - 1 >= 0) neighbours.push_back(Coords(xChosen, yChosen - 1));
		if (yChosen + 1 < (int)N) neighbours.push_back(Coords(xChosen, yChosen + 1));
		if (xChosen - 1 >= 0) neighbours.push_back(Coords(xChosen - 1, yChosen));
		if (xChosen + 1 < (int)M) neighbours.push_back(Coords(xChosen + 1, yChosen));

		for (Coords ngb : neighbours)
		{
			if (helper[ngb.getX()][ngb.getY()] != NOTHING)
				continue;

			bool colorWhite = rand() <  probability * ((double)RAND_MAX + 1.0);

			helper[ngb.getX()][ngb.getY()] = BLACK;
			if (colorWhite)
			{
				matrix[ngb.getX()][ngb.getY()] = true;
				helper[ngb.getX()][ngb.getY()] = WHITE;
				queue.push_back(ngb);
				whiteCollection.push_back(ngb);
				++currNumberWhite;

				if (currNumberWhite == numberWhite)
				{
					preparing = false;
					break;
				}
			}
		}

		if (queue.empty() && currNumberWhite != numberWhite)
		{
			for (unsigned r_idx = 0; r_idx < M; ++r_idx)
			{
				for (unsigned c_idx = 0; c_idx < N; ++c_idx)
				{
					if (helper[r_idx][c_idx] == BLACK)
						helper[r_idx][c_idx] = NOTHING;
				}
			}

			queue = whiteCollection;
		}
	}

	unsigned beginIdx = rand() % whiteCollection.size();
	Coords begin = whiteCollection[beginIdx];

	std::swap(whiteCollection[beginIdx], whiteCollection[whiteCollection.size() - 1]);
	whiteCollection.pop_back();

	unsigned endIdx = rand() % whiteCollection.size();
	Coords end = whiteCollection[endIdx];

	Raster raster(M, N, matrix, begin, end);

	MyMatrix<bool>::deleteMatrix(M, matrix);
	MyMatrix<char>::deleteMatrix(M, helper);

	return raster;
}


long long DataGenerator::getAlgorithmAverageTime(unsigned M, unsigned N, DataGenerator::Algorithm algorithm)
{
	srand((unsigned)time(nullptr));

	std::function<long long(Raster, bool)> findShortestPath;

	switch (algorithm)
	{
	case BELLMAN_FORD:
		findShortestPath = BellmanFord::findShortestPath;
		break;
	case DIJKSTRA_TABLE:
		findShortestPath = Dijkstra::findShortestPath_Table;
		break;
	case DIJKSTRA_HEAP:
		findShortestPath = Dijkstra::findShortestPath_Heap;
		break;
	case A_STAR:
		findShortestPath = AStar::findShortestPath;
		break;
	default:
		return 0;
	}

	long long time = 0;

	int iterations = 5;

	for (int i_idx = 0; i_idx < iterations; ++i_idx)
	{
		double probability = 0.7 + ((rand() % 16) / 100.0);
		Raster raster = DataGenerator::createRandomParameterized(M, N, probability);
		long long t = findShortestPath(raster, true);
		time += t;
	}
	time /= iterations;

	return time;
}


long long DataGenerator::calculateTimeNN(unsigned M, unsigned N)
{
	return (long long)(M * N * M * N);
}


long long DataGenerator::calculateTimeNLogN(unsigned M, unsigned N)
{
	return (long long)(M * N * std::log(M * N));
}


Raster DataGenerator::getFromStandardStream()
{
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	std::cout << "Enter each line. To finish enter empty line.\n";

	std::vector<std::string> lines;
	std::string row;

	std::getline(std::cin, row);
	unsigned columns = row.length();

	while (!row.empty())
	{
		if (row.length() != columns)
		{
			return Raster();
		}
		lines.push_back(row);

		std::getline(std::cin, row);
	}

	Raster raster = DataGenerator::createFromVector(lines);
	return raster;
}


Raster DataGenerator::getFromFileStream()
{
	std::ifstream reader;
	std::string path;

	std::cout << "Path = ";
	std::cin >> path;

	reader.open(path);
	if (!reader.is_open())
		return Raster();

	std::vector<std::string> lines;
	std::string row;

	reader >> row;
	unsigned columns = row.length();

	while (!reader.eof())
	{
		if (row.length() != columns)
		{
			return Raster();
		}
		lines.push_back(row);

		reader >> row;
	}

	Raster raster = DataGenerator::createFromVector(lines);
	return raster;
}


Raster DataGenerator::getRandomParameterized()
{
	unsigned M, N;
	double probability;

	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << "M = ";
	std::cin >> M;

	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << "N = ";
	std::cin >> N;

	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << "Probability of white field = ";
	std::cin >> probability;

	if (M <= 0 || N <= 0 || probability > 1)
	{
		return Raster();
	}

	Raster raster = DataGenerator::createRandomParameterized(M, N, probability);
	return raster;
}


std::vector<TableLine> DataGenerator::generateStatistics()
{
	int chosen;
	unsigned M, N, step;
	std::vector<TableLine> lines;
	std::function<long long(unsigned, unsigned)> calculateT_n;
	Algorithm algorithm;

	std::cout << "Choose algorithm: \n";
	std::cout << "1 - Bellman-Ford\n2 - Dijkstra (Table)\n3 - Dijkstra (Heap)\n4 - A Star\n";

	std::cin >> chosen;
	if (chosen < 1 || chosen > 4)
		return lines;

	switch (chosen)
	{
	case BELLMAN_FORD:
		algorithm = BELLMAN_FORD;
		calculateT_n = calculateTimeNN;
		break;
	case DIJKSTRA_TABLE:
		algorithm = DIJKSTRA_TABLE;
		calculateT_n = calculateTimeNN;
		break;
	case DIJKSTRA_HEAP:
		algorithm = DIJKSTRA_HEAP;
		calculateT_n = calculateTimeNLogN;
		break;
	case A_STAR:
		algorithm = A_STAR;
		calculateT_n = calculateTimeNLogN;
		break;
	default:
		return lines;
	}

	std::cout << "M = ";
	std::cin >> M;

	std::cout << "N = ";
	std::cin >> N;

	std::cout << "step = ";
	std::cin >> step;

	for (int i_idx = 0; i_idx < 11; ++i_idx)
	{
		unsigned n = M * N;
		long long T_n = calculateT_n(M, N);
		long long t_n = DataGenerator::getAlgorithmAverageTime(M, N, algorithm);

		TableLine tableLine(n, t_n, T_n);
		lines.push_back(tableLine);

		std::swap(M, N);
		M += step;
		N += step;
	}

	unsigned median_idx = (lines.size() + 1) / 2;

	double median_q_part = lines[median_idx].get_T_n() / ((double)lines[median_idx].get_t_n());

	for (unsigned i_idx = 0; i_idx < lines.size(); ++i_idx)
	{
		double rest_q_part = lines[i_idx].get_t_n() / ((double)lines[i_idx].get_T_n());
		lines[i_idx].set_q(median_q_part * rest_q_part);
	}

	return lines;
}

