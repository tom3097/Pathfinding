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

	bool ** matrix = BoolMatrix::createBoolMatrix(M, N, false);

	for (int l_idx = 0; l_idx < M; ++l_idx)
	{
		for (int c_idx = 0; c_idx < N; ++c_idx)
		{
			if (lines[l_idx][c_idx] == BEGIN)
			{
				if (beginSet)
				{
					BoolMatrix::deleteBoolMatrix(M, matrix);
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
					BoolMatrix::deleteBoolMatrix(M, matrix);
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
				BoolMatrix::deleteBoolMatrix(M, matrix);
				return Raster();
			}
		}
	}

	if (!beginSet || !endSet)
	{
		BoolMatrix::deleteBoolMatrix(M, matrix);
		return Raster();
	}

	Raster raster(M, N, matrix, begin, end);
	BoolMatrix::deleteBoolMatrix(M, matrix);
	return raster;
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
	//toDo
	return Raster();
}


Raster DataGenerator::getRandom()
{
	//toDo
	return Raster();
}
