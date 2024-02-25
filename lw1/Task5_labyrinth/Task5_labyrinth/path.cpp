#include "path.h"

std::string GetLineUp(size_t y, SearchData& searchData)
{
	std::string line;
	if (y > 0)
	{
		searchData.inputFile.seekg(0, searchData.linePositions[y - 1]);
		std::getline(searchData.inputFile, line);
	}
	return line;
}

std::string GetLineCurrent(size_t y, SearchData& searchData)
{
	std::string line;
	searchData.inputFile.seekg(searchData.linePositions[y]);
	std::getline(searchData.inputFile, line);
	return line;
}

std::string GetLineDown(size_t y, SearchData& searchData)
{
	std::string line;
	if (y < maxSize - 1 && searchData.linePositions[y + 1] < searchData.inputFile.end)
	{
		searchData.inputFile.seekg(searchData.linePositions[y + 1]);
		std::getline(searchData.inputFile, line);
	}
	return line;
}

float GetModule(Point self, Point target)
{
	size_t offsetX = target.x - self.x;
	size_t offsetY = target.y - self.y;
	return (float)std::sqrt(offsetX * offsetX + offsetY * offsetY);
}

std::shared_ptr<Node> GetPath(SearchData& searchData)
{
	std::shared_ptr<Node> startNode = std::make_shared<Node>(searchData.A);

	std::set<Point> closedSet;
	std::vector<std::vector<std::shared_ptr<Node>>> openSet(maxSize, std::vector<std::shared_ptr<Node>>(maxSize));
	for (size_t i = 0; i < maxSize; i++)
		for (size_t j = 0; j < maxSize; j++)
			openSet[i][j] = nullptr;

	std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>> queue;

	std::ifstream& file = searchData.inputFile;

	startNode->isInQueue = true;
	openSet[startNode->point.y][startNode->point.x] = startNode;
	queue.push(startNode);
	
	while (!queue.empty())
	{
		auto currentNode = queue.top();
		currentNode->isInQueue = false;
		queue.pop();

		Point currentPoint = currentNode->point;

		if (currentPoint == searchData.B)
		{
			startNode = currentNode->parent;
			return startNode;
		}

		closedSet.insert(currentNode->point);

		Point neighbors[4] = { Point{}, Point{}, Point{}, Point{} };
		Point neighbor{};

		std::string lineUp = GetLineUp(currentPoint.y, searchData);
		std::string lineCurrent = GetLineCurrent(currentPoint.y, searchData);
		std::string lineDown = GetLineDown(currentPoint.y, searchData);

		if (currentPoint.x < lineUp.length() && lineUp[currentPoint.x] != '#')
		{
			Point p;
			p.x = currentPoint.x;
			p.y = currentPoint.y - 1;
			neighbors[UP] = p;
		}

		if (currentPoint.x < lineCurrent.length() - 1 && lineCurrent[currentPoint.x + 1] != '#')
		{
			Point p;
			p.x = currentPoint.x + 1;
			p.y = currentPoint.y;
			neighbors[RIGHT] = p;
		}

		if (currentPoint.x < lineDown.length() && lineDown[currentPoint.x] != '#')
		{
			Point p;
			p.x = currentPoint.x;
			p.y = currentPoint.y + 1;
			neighbors[DOWN] = p;
		}

		if (currentPoint.x > 0 && lineCurrent[currentPoint.x - 1] != '#')
		{
			Point p;
			p.x = currentPoint.x - 1;
			p.y = currentPoint.y;
			neighbors[LEFT] = p;
		}
		
		float newBefore = currentNode->before + 1.f;
		
		for (size_t i = 0; i < 4; i++)
		{
			Point neighbor = neighbors[i];
			if (neighbor.x == maxSize || closedSet.count(neighbor))
				continue;
			std::shared_ptr<Node> neighborNode = openSet[neighbor.y][neighbor.x];
			float newAfter = 0.f;
			if (neighborNode)
			{
				if (neighborNode->isInQueue && newBefore < neighborNode->before)
				{
					auto queueSize = queue.size();
					auto hold = std::make_unique<std::shared_ptr<Node>[]>(queueSize);
					for (size_t j = 0; j < queueSize; j++)
					{
						hold[j] = queue.top();
						queue.pop();
						if (hold[j]->point == neighbor)
						{
							hold[j]->before = newBefore;
							hold[j]->updateSum();
							hold[j]->parent = openSet[currentNode->point.y][currentNode->point.x];
						}
					}
					for (size_t j = 0; j < queueSize; j++)
						queue.push(hold[j]);
				}
			}
			else
			{
				auto newNode = std::make_shared<Node>(neighbor);
				openSet[neighbor.y][neighbor.x] = newNode;
				newNode->before = newBefore;
				newNode->after = GetModule(neighbor, searchData.B);
				newNode->updateSum();
				newNode->parent = openSet[currentNode->point.y][currentNode->point.x];
				newNode->isInQueue = true;
				queue.push(newNode);
			}
		}
	}
	return nullptr;
}