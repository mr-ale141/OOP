#pragma once
#include <string>
#include <cmath>
#include "ICanvasDrawable.h"

class IShape : public ICanvasDrawable
{
public:
	virtual ~IShape() = default;

	virtual double GetArea() const = 0;
	virtual double GetPerimeter() const = 0;
	virtual std::string ToString() const = 0;
	virtual uint32_t GetOutlineColor() const = 0;

protected:
	IShape() = default;
	
	//статические методы отдельно в класс
	static double GetModule(const CPoint& p1, const CPoint& p2)
	{
		const auto offset = p2 - p1;
		return std::sqrt(offset.m_x * offset.m_x + offset.m_y * offset.m_y);
	}
	// std::move for namePoint
	static std::string PointToString(const CPoint& point, std::string&& namePoint)
	{
		std::string str;
		str += namePoint + ": x = " + std::to_string(point.m_x);
		str += " y = " + std::to_string(point.m_y);
		str += "\n";
		return str;
	}
}; 
