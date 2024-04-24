#pragma once
#include "CSolidShape.h"

class CCircle : public CSolidShape
{
public:
	CCircle(
		const CPoint& center, 
		double radius,
		uint32_t outlineColor,
		uint32_t fillColor
	);
	~CCircle() = default;

	void Draw(ICanvas& canvas) const override;

	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;

	CPoint GetCenter() const;
	double GetRadius() const;

private:
	CPoint m_center;
	double m_radius;
	// ?????? ? ?????? ? ???????
	const std::string m_name = "Circle";
};