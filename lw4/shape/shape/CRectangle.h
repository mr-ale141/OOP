#pragma once
#include "ISolidShape.h"

class CRectangle : public ISolidShape
{
public:
	CRectangle(
		const CPoint& leftTop,
		const CPoint& rightBottom,
		double width,
		double height,
		uint32_t outlineColor,
		uint32_t fillColor
	);
	~CRectangle();

	void Draw(ICanvas& canvas) const override;

	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	uint32_t GetOutlineColor() const override;

	uint32_t GetFillColor() const override;

	CPoint GetLeftTop() const;
	CPoint GetRightBottom() const;
	double GetWidth() const;
	double GetHeight() const;

	static ShapePtr CreateInstance(
		const CPoint& leftTop,
		const CPoint& rightBottom,
		double width,
		double height,
		uint32_t outlineColor,
		uint32_t fillColor
	);

private:
	CPoint m_leftTop;
	CPoint m_rightBottom;
	double m_width;
	double m_height;
	uint32_t m_outlineColor;
	uint32_t m_fillColor;
};