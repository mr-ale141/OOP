#include "CTriangle.h"

CTriangle::CTriangle(
	const CPoint& vertex1, 
	const CPoint& vertex2, 
	const CPoint& vertex3,
	uint32_t outlineColor,
	uint32_t fillColor
)
	: CSolidShape(outlineColor, fillColor),
	m_vertex1(vertex1), m_vertex2(vertex2), m_vertex3(vertex3)
{}

void CTriangle::Draw(ICanvas& canvas) const
{
	auto lineColor = GetOutlineColor();
	auto fillColor = GetFillColor();

	canvas.DrawLine(m_vertex1, m_vertex2, lineColor);
	canvas.DrawLine(m_vertex2, m_vertex3, lineColor);
	canvas.DrawLine(m_vertex3, m_vertex1, lineColor);

	std::vector<CPoint> points{m_vertex1, m_vertex2, m_vertex3};

	canvas.FillPolygon(points, fillColor);
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
	std::string str("Type: " + m_name + "\n");
	str += PointToString(m_vertex1, "Vertex 1");
	str += PointToString(m_vertex2, "Vertex 2");
	str += PointToString(m_vertex3, "Vertex 3");
	return str;
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
