#pragma once
#include <string>
#include <memory>
#include <cmath>
#include "ICanvasDrawable.h"

class IShape : public ICanvasDrawable
{
public:

	virtual double GetArea() const = 0;
	virtual double GetPerimeter() const = 0;
	virtual std::string ToString() const = 0;
	virtual uint32_t GetOutlineColor() const = 0;

protected:

	IShape() = default;
	~IShape() = default;

	static double GetModule(const CPoint& p1, const CPoint& p2)
	{
		auto offset = p2 - p1;
		return std::sqrt(offset.m_x * offset.m_x + offset.m_y * offset.m_y);
	}
}; 

using ShapePtr = std::unique_ptr<IShape, ICanvasDrawable::Deleter>;