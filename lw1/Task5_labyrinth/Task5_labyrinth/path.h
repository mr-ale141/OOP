#pragma once
#include <queue>
#include <set>
#include <fstream>
#include <memory>
#include <iostream>
#include <string>
#include <cmath>
#include <vector>

static const size_t maxSize = 100;
static const int countSides = 4;

// enum class
enum Direction
{
	UP,
	RIGHT,
	DOWN,
	LEFT,
	UNKNOWN,
};

struct Point
{
	size_t x;
	size_t y;
	explicit Point()
	{
		x = maxSize;
		y = maxSize;
	}
	//inicial list не подходит
	explicit Point(std::initializer_list<size_t> args)
	{
		x = args.begin()[0];
		y = args.begin()[1];
	}
	//убрать
	Point& operator=(std::initializer_list<size_t> args)
	{
		x = args.begin()[0];
		y = args.begin()[1];
		return *this;
	}
	Point& operator=(const Point& p)
	{
		x = p.x;
		y = p.y;
		return *this;
	}
	bool operator==(const Point& p) const
	{
		if (x != p.x || y != p.y)
			return false;
		else
			return true;
	}
	bool operator!=(const Point& p) const
	{
		if (x == p.x && y == p.y)
			return false;
		else
			return true;
	}
	bool operator<(const Point& p) const
	{
		if (x != p.x)
			return x < p.x;
		else
			return y < p.y;
	}
};

class Node
{
public:
	Node()
	{
		point = { maxSize, maxSize };
		before = 0.f;
		after = 0.f;
		sum = 0.f;
		directionForThis = UNKNOWN;
		isInQueue = false;
	}
	explicit Node(const Point newPoint)
	{
		point = newPoint;
		before = 0.f;
		after = 0.f;
		sum = 0.f;
		directionForThis = UNKNOWN;
		isInQueue = false;
	}
	void updateSum()
	{
		sum = before + after;
	}
	Point point;
	float before = 0.0f;
	float after;
	float sum;
	bool isInQueue;
	Direction directionForThis;
	//обрать лич
	bool operator<(const Node& n) const
	{
		return sum > n.sum;
	}
 // умеет сам
	Node& operator=(const Node& n)
	{
		point = n.point;
		before = n.before;
		after = n.after;
		sum = n.sum;
		isInQueue = n.isInQueue;
		directionForThis = n.directionForThis;
		return *this;
	}
};

struct CompareNodes {
	bool operator()(const Node* left, const Node* right)
	{
		return left->sum > right->sum;
	}
};

struct SearchData
{
// 
	std::streampos linePositions[maxSize];
	Point A;
	Point B;
	std::ifstream inputFile;//лишнее необходимо отвязаться от файла
	size_t fileSize;
// одномерный массив с расчетом индекса
	std::vector<std::vector<Node>> openSet;
// зарание выделить память
	std::priority_queue<Node*, std::vector<Node*>, CompareNodes> queue;
};

Node GetPath(SearchData& searchData);
