#pragma once
#include "CSolidShape.h"

class CRectangle : public CSolidShape
{
public:
	CRectangle(
		const CPoint& leftTop,
		double width,
		double height,
		uint32_t outlineColor,
		uint32_t fillColor
	);
	~CRectangle() = default;

	void Draw(ICanvas& canvas) const override;

	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;

	CPoint GetLeftTop() const;
	CPoint GetRightBottom() const;
	double GetWidth() const;
	double GetHeight() const;

private:
	CPoint m_leftTop;
	double m_width;
	double m_height;
	const std::string m_name = "Rectangle";
};