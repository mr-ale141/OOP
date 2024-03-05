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

std::vector<std::vector<Node>> GetOpenSet()
{
	std::vector<std::vector<Node>> openSet(maxSize, std::vector<Node>(maxSize));
	for (size_t i = 0; i < maxSize; i++)
		for (size_t j = 0; j < maxSize; j++)
			openSet[i][j] = Node();
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

Direction GetDirection(const Point& parent, const Point& current)
{
	Direction directionForCurrent = UNKNOWN;
	if (parent.x < current.x)
		directionForCurrent = RIGHT;
	if (parent.x > current.x)
		directionForCurrent = LEFT;
	if (parent.y > current.y)
		directionForCurrent = UP;
	if (parent.y < current.y)
		directionForCurrent = DOWN;
	return directionForCurrent;
}

void UpdateNodeInQueue(
	SearchData& searchData,
	const Point& neighbor,
	const Node& currentNode,
	const float newBefore
)
{
	auto queueSize = searchData.queue.size();
	std::vector<Node*> hold(queueSize);
	for (size_t j = 0; j < queueSize; j++)
	{
		hold[j] = searchData.queue.top();
		
		//std::cout << "J=" << j << "|X=" << hold[j]->point.x + 1 << "|Y=" << hold[j]->point.y + 1 << "|bf=" << hold[j]->before << "|af=" << hold[j]->after << "|sum=" << hold[j]->sum << std::endl;
		searchData.queue.pop();
		if (hold[j]->point == neighbor)
		{
			hold[j]->before = newBefore;
			hold[j]->updateSum();
			hold[j]->directionForThis = GetDirection(currentNode.point, neighbor);
		}
	}
	for (size_t j = 0; j < queueSize; j++)
		searchData.queue.push(hold[j]);
}

void PushNewNode(
	const Node& currentNode,
	SearchData& searchData,
	const Point& neighbor,
	const float newBefore
)
{
	auto newNode = Node(neighbor);
	newNode.before = newBefore;
	newNode.after = GetModule(neighbor, searchData.B);
	newNode.updateSum();
	newNode.directionForThis = GetDirection(currentNode.point, neighbor);
	newNode.isInQueue = true;
	searchData.openSet[neighbor.y][neighbor.x] = newNode;
	//std::cout << "newNode: X=" << newNode.point.x + 1 << "|Y=" << newNode.point.y + 1 << "|bf=" << newNode.before << "|af=" << newNode.after << "|sum=" << newNode.sum << std::endl;
	searchData.queue.push(&(searchData.openSet[neighbor.y][neighbor.x]));
}

Node GetPath(SearchData& searchData)
{
	Node startNode(searchData.A);

	std::set<Point> closedSet;
	searchData.openSet = GetOpenSet();

	std::ifstream& file = searchData.inputFile;

	startNode.isInQueue = true;
	searchData.openSet[startNode.point.y][startNode.point.x] = startNode;
	searchData.queue.push(&(searchData.openSet[startNode.point.y][startNode.point.x]));
	
	while (!searchData.queue.empty())
	{
		Node* currentNode = searchData.queue.top();
		currentNode->isInQueue = false;
		searchData.queue.pop();
		//std::cout << "currentNode: X=" << currentNode->point.x + 1 << "|Y=" << currentNode->point.y + 1 << "|bf=" << currentNode->before << "|af=" << currentNode->after << "|sum=" << currentNode->sum << std::endl;
		Point currentPoint = currentNode->point;
		if (currentPoint == searchData.B)
			return *currentNode;

		closedSet.insert(currentNode->point);

		auto lineUp = GetLineUp(currentPoint.y, searchData);
		auto lineCurrent = GetLineCurrent(currentPoint.y, searchData);
		auto lineDown = GetLineDown(currentPoint.y, searchData);

		auto neighbors = GetNeighbors(lineUp, lineCurrent, lineDown, currentPoint);
		
		float newBefore = currentNode->before + 1.f;
		
		for (size_t i = 0; i < countSides; i++)
		{
			Point neighbor = neighbors[i];
			if (neighbor.x == maxSize || closedSet.count(neighbor))
				continue;
			Node neighborNode = searchData.openSet[neighbor.y][neighbor.x];
			if (neighborNode.directionForThis != UNKNOWN)
			{
				if (neighborNode.isInQueue && newBefore < neighborNode.before)
					UpdateNodeInQueue(searchData, neighbor, *currentNode, newBefore);
			}
			else
			{
				PushNewNode(*currentNode, searchData, neighbor, newBefore);
			}
		}
	}
	return Node();
}