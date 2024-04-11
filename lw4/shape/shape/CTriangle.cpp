#include "CTriangle.h"

CTriangle::CTriangle(
	const CPoint& vertex1, 
	const CPoint& vertex2, 
	const CPoint& vertex3,
	uint32_t outlineColor,
	uint32_t fillColor
)
	: 
	m_vertex1(vertex1), m_vertex2(vertex2), m_vertex3(vertex3),
	m_outlineColor(outlineColor), m_fillColor(fillColor)
{}

CTriangle::~CTriangle()
{}

void CTriangle::Draw(ICanvas& canvas) const
{
	std::cout << "not now" << std::endl;
}

double CTriangle::GetArea() const
{
	return std::abs(
		(m_vertex2.m_x - m_vertex1.m_x) * (m_vertex3.m_y - m_vertex1.m_y) - 
		(m_vertex3.m_x - m_vertex1.m_x) * (m_vertex2.m_y - m_vertex1.m_y)
	) / 2;
};

double CTriangle::GetPerimeter() const
{
	return
		GetModule(m_vertex1, m_vertex2) +
		GetModule(m_vertex2, m_vertex3) +
		GetModule(m_vertex3, m_vertex1);
}

std::string CTriangle::ToString() const
{
	return std::string("Triangle");
}

uint32_t CTriangle::GetOutlineColor() const
{
	return m_outlineColor;
}

uint32_t CTriangle::GetFillColor() const
{
	return m_fillColor;
}

CPoint CTriangle::GetVertex1() const
{
	return m_vertex1;
}

CPoint CTriangle::GetVertex2() const
{
	return m_vertex2;
}

CPoint CTriangle::GetVertex3() const
{
	return m_vertex3;
}

ShapePtr CTriangle::CreateInstance(
	const CPoint& vertex1,
	const CPoint& vertex2,
	const CPoint& vertex3,
	const uint32_t outlineColor,
	const uint32_t fillColor
)
{
	return ShapePtr(
		new CTriangle(
			vertex1,
			vertex2,
			vertex3,
			outlineColor,
			fillColor
		)
	);
}