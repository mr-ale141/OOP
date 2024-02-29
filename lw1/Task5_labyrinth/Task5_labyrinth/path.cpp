#include "path.h"

float GetModule(const Point self, const Point target)
{
	size_t offsetX = target.x - self.x;
	size_t offsetY = target.y - self.y;
	return (float)std::sqrt(offsetX * offsetX + offsetY * offsetY);
}

std::string GetLineUp(const size_t y, SearchData& searchData)
{
	std::string line;
	if (y > 0)
	{
		searchData.inputFile.seekg(searchData.linePositions[y - 1]);
		std::getline(searchData.inputFile, line);
	}
	return line;
}

std::string GetLineCurrent(const size_t y, SearchData& searchData)
{
	std::string line;
	searchData.inputFile.seekg(searchData.linePositions[y]);
	std::getline(searchData.inputFile, line);
	return line;
}

std::string GetLineDown(const size_t y, SearchData& searchData)
{
	std::string line;
	if ((y + 1) < searchData.fileSize)
	{
		searchData.inputFile.seekg(searchData.linePositions[y + 1]);
		std::getline(searchData.inputFile, line);
	}
	return line;
}

std::vector<std::vector<std::shared_ptr<Node>>> GetOpenSet()
{
	std::vector<std::vector<std::shared_ptr<Node>>> openSet(maxSize, std::vector<std::shared_ptr<Node>>(maxSize));
	for (size_t i = 0; i < maxSize; i++)
		for (size_t j = 0; j < maxSize; j++)
			openSet[i][j] = nullptr;
	return openSet;
}

std::vector<Point> GetNeighbors(
	const std::string& lineUp,
	const std::string& lineCurrent,
	const std::string& lineDown,
	const Point& currentPoint)
{
	std::vector<Point> neighbors(4);

	if ((currentPoint.x < lineUp.length()) && (lineUp[currentPoint.x] != '#'))
		neighbors[UP] = { currentPoint.x, currentPoint.y - 1 };

	if ((currentPoint.x < (lineCurrent.length() - 1)) && (lineCurrent[currentPoint.x + 1] != '#'))
		neighbors[RIGHT] = { currentPoint.x + 1, currentPoint.y };

	if ((currentPoint.x < lineDown.length()) && (lineDown[currentPoint.x] != '#'))
		neighbors[DOWN] = { currentPoint.x, currentPoint.y + 1 };

	if ((currentPoint.x > 0) && (lineCurrent[currentPoint.x - 1] != '#'))
		neighbors[LEFT] = { currentPoint.x - 1, currentPoint.y };

	return neighbors;
}

void UpdateNodeInQueue(
	std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, CompareNodes>& queue,
	const std::vector<std::vector<std::shared_ptr<Node>>>& openSet,
	const Point& neighbor,
	const std::shared_ptr<Node>& currentNode,
	const float newBefore
)
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

void PushNewNode(
	std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, CompareNodes>& queue,
	std::vector<std::vector<std::shared_ptr<Node>>>& openSet,
	const std::shared_ptr<Node>& currentNode,
	const SearchData& searchData,
	const Point& neighbor,
	const float newBefore
)
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

std::shared_ptr<Node> GetPath(SearchData& searchData)
{
	std::shared_ptr<Node> startNode = std::make_shared<Node>(searchData.A);

	std::set<Point> closedSet;
	auto openSet = GetOpenSet();

	std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, CompareNodes> queue;

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
			return currentNode->parent;

		closedSet.insert(currentNode->point);

		auto lineUp = GetLineUp(currentPoint.y, searchData);
		auto lineCurrent = GetLineCurrent(currentPoint.y, searchData);
		auto lineDown = GetLineDown(currentPoint.y, searchData);

		auto neighbors = GetNeighbors(lineUp, lineCurrent, lineDown, currentPoint);
		
		float newBefore = currentNode->before + 1.f;
		
		for (size_t i = 0; i < 4; i++)
		{
			Point neighbor = neighbors[i];
			if (neighbor.x == maxSize || closedSet.count(neighbor))
				continue;
			std::shared_ptr<Node> neighborNode = openSet[neighbor.y][neighbor.x];
			if (neighborNode)
			{
				if (neighborNode->isInQueue && newBefore < neighborNode->before)
					UpdateNodeInQueue(queue, openSet, neighbor, currentNode, newBefore);
			}
			else
			{
				PushNewNode(queue, openSet, currentNode, searchData, neighbor, newBefore);
			}
		}
	}
	return nullptr;
}