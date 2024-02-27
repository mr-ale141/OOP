#pragma once
#include <queue>
#include <set>
#include <memory>
#include <fstream>
#include <iostream>
#include <string>
#include <cmath>

static const size_t maxSize = 100;

enum Direction
{
	UP,
	RIGHT,
	DOWN,
	LEFT
};

struct Point
{
	size_t x = maxSize;
	size_t y = maxSize;
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

struct SearchData
{
	std::streampos linePositions[maxSize];
	Point A;
	Point B;
	std::ifstream inputFile;
	size_t fileSize;
};

class Node
{
public:
	explicit Node(Point newPoint)
	{
		point = newPoint;
		before = 0.f;
		after = 0.f;
		sum = 0.f;
		parent = nullptr;
		isInQueue = false;
	}
	void updateSum()
	{
		sum = before + after;
	}
	Point point;
	float before;
	float after;
	float sum;
	bool isInQueue;
	std::shared_ptr<Node> parent;
};

struct CompareNodes {
	bool operator()(std::shared_ptr<Node> const& left, std::shared_ptr<Node> const& right)
	{
		return left->sum > right->sum;
	}
};

std::shared_ptr<Node> GetPath(SearchData& searchData);