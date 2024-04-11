#pragma once
#include "ISolidShape.h"

class CTriangle : public ISolidShape
{
public:
	CTriangle(
		const CPoint& vertex1, 
		const CPoint& vertex2, 
		const CPoint& vertex3,
		uint32_t outlineColor,
		uint32_t fillColor
	);

	~CTriangle();

	void Draw(ICanvas& canvas) const override;

	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	uint32_t GetOutlineColor() const override;
	
	uint32_t GetFillColor() const override;

	CPoint GetVertex1() const;
	CPoint GetVertex2() const;
	CPoint GetVertex3() const;

	static ShapePtr CreateInstance(
		const CPoint& vertex1,
		const CPoint& vertex2,
		const CPoint& vertex3,
		const uint32_t outlineColor,
		const uint32_t fillColor
	);

private:
	CPoint m_vertex1;
	CPoint m_vertex2;
	CPoint m_vertex3;
	uint32_t m_outlineColor;
	uint32_t m_fillColor;
};
