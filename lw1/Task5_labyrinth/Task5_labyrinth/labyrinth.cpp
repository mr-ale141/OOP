#include "labyrinth.h"
#include "path.h"

SearchData FindPoints(std::string& inputFileName)
{
	SearchData searchData{};
	for (size_t i = 0; i < maxSize; i++)
		searchData.linePositions[i] = searchData.inputFile.end;

	searchData.inputFile.open(inputFileName);
	if (!searchData.inputFile)
		throw std::ios_base::failure("ERROR! Can't open " + inputFileName);

	searchData.inputFile.seekg(0, std::ios_base::beg);

	bool isFoundA = false;
	bool isFoundB = false;

	std::string line;

	size_t x{};
	size_t y{};

	searchData.linePositions[y] = searchData.inputFile.tellg();
	while (std::getline(searchData.inputFile, line) && y < maxSize)
	{
		if ((x = line.find('A')) != std::string::npos)
		{
			searchData.A.x = x;
			searchData.A.y = y;
			if (isFoundA)
				throw std::invalid_argument("ERROR! Input file contains 'A' many times");
			isFoundA = true;
		}
		if ((x = line.find('B')) != std::string::npos)
		{
			searchData.B.x = x;
			searchData.B.y = y;
			if (isFoundB)
				throw std::invalid_argument("ERROR! Input file contains 'B' many times");
			isFoundB = true;
		}
		y++;
		searchData.linePositions[y] = searchData.inputFile.tellg();
	}

	if (!isFoundA || !isFoundB)
		throw std::invalid_argument("ERROR! Input file not contains 'A', 'B'");

	return searchData;
}

void FindPath(std::string& inputFileName, std::string& outputFileName)
{

	SearchData searchData = FindPoints(inputFileName);

	std::ofstream outputFile(outputFileName, std::fstream::trunc);
	if (!outputFile)
		throw std::ios_base::failure("ERROR! Can't open " + outputFileName);

	auto currentNode = GetPath(searchData);

	searchData.inputFile.seekg(0, std::ios_base::beg);
	for (char ch; searchData.inputFile.get(ch);) outputFile.put(ch);
	outputFile.close();

	std::fstream file(outputFileName, std::fstream::in | std::fstream::out | std::fstream::binary);

	while (currentNode)
	{
		file.seekp(currentNode->point.x, searchData.linePositions[currentNode->point.y]);
		file.write((char *)'.', sizeof(char));
		currentNode = currentNode->parent;
	}

	if (!file.flush())
		throw std::ios_base::failure("ERROR! Can't write in output file");

	searchData.inputFile.close();
	file.close();
}