#pragma once
#include "ISolidShape.h"

class CCircle : public ISolidShape
{
public:
	CCircle(
		const CPoint& center, 
		double radius,
		uint32_t outlineColor,
		uint32_t fillColor
	);
	~CCircle();

	void Draw(ICanvas& canvas) const override;

	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	uint32_t GetOutlineColor() const override;

	uint32_t GetFillColor() const override;

	CPoint GetCenter() const;
	double GetRadius() const;

	static ShapePtr CreateInstance(
		const CPoint& center,
		double radius,
		uint32_t outlineColor,
		uint32_t fillColor
	);

private:
	CPoint m_center;
	double m_radius;
	uint32_t m_outlineColor;
	uint32_t m_fillColor;
};