#pragma once
#include "IShape.h"

class CLineSegment : public IShape
{
public:
	CLineSegment(const CPoint& startPoint, const CPoint& endPoint, uint32_t outlineColor);
	~CLineSegment();

	void Draw(ICanvas& canvas) const override;

	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	uint32_t GetOutlineColor() const override;

	CPoint GetStartPoint() const;
	CPoint GetEndPoint() const;

	static ShapePtr CreateInstance(const CPoint& startPoint, const CPoint& endPoint, uint32_t outlineColor);

private:
	CPoint m_startPoint;
	CPoint m_endPoint;
	uint32_t m_outlineColor;
};
