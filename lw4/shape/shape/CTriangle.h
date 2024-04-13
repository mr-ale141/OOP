#pragma once
#include "CSolidShape.h"

class CTriangle : public CSolidShape
{
public:
	CTriangle(
		const CPoint& vertex1, 
		const CPoint& vertex2, 
		const CPoint& vertex3,
		uint32_t outlineColor,
		uint32_t fillColor
	);

	~CTriangle() = default;

	void Draw(ICanvas& canvas) const override;

	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	
	CPoint GetVertex1() const;
	CPoint GetVertex2() const;
	CPoint GetVertex3() const;

private:
	CPoint m_vertex1;
	CPoint m_vertex2;
	CPoint m_vertex3;
	const std::string m_name = "Triangle";
};
