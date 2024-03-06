#include "labyrinth.h"
#include "path.h"
#include <exception>

// считывать сразу в опенсет
SearchData FindPoints(const std::string& inputFileName)
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

	searchData.fileSize = y;

	searchData.inputFile.clear();

	if (!isFoundA || !isFoundB)
		throw std::invalid_argument("ERROR! Input file not contains 'A', 'B'");

	return searchData;
}

Point GetParentPoint(const Node& node)
{
	switch (node.directionForThis)
	{
	case UP:
		return Point({ node.point.x, node.point.y + 1 });
	case RIGHT:
		return Point({ node.point.x - 1, node.point.y });
		break;// лишнее ретурн
	case DOWN:
		return Point({ node.point.x, node.point.y - 1 });
		break;
	case LEFT:
		return Point({ node.point.x + 1, node.point.y });
		break;
	default:
		throw std::invalid_argument("Not correct direction");
		break;
	}
}

void FindPath(const std::string& inputFileName, const std::string& outputFileName)
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
	if (!file)
		throw std::ios_base::failure("ERROR! Can't open " + outputFileName);

	char ch = '.';

	while (currentNode.directionForThis != UNKNOWN)
	{
		Point point = currentNode.point;
		Point parentPoint = GetParentPoint(currentNode);
		if (point == searchData.A || point == searchData.B)
		{
			currentNode = searchData.openSet[parentPoint.y][parentPoint.x];
			continue;
		}
		std::streampos pos = searchData.linePositions[point.y] + (std::streamoff)point.x;
		file.seekp(pos);
		file.write((char *)&ch, sizeof(char));
		currentNode = searchData.openSet[parentPoint.y][parentPoint.x];
	}



	if (!file.flush())
		throw std::ios_base::failure("ERROR! Can't write in output file");

	searchData.inputFile.close();
	file.close();
}