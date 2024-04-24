#include "CCircle.h"

CCircle::CCircle(
	const CPoint& center, 
	double radius,
	uint32_t outlineColor,
	uint32_t fillColor
)
	: CSolidShape(outlineColor, fillColor),
	m_center(center), m_radius(radius)
{}

void CCircle::Draw(ICanvas& canvas) const
{
	auto lineColor = GetOutlineColor();
	auto fillColor = GetFillColor();

	canvas.DrawCircle(m_center, m_radius, lineColor);
	canvas.FillCircle(m_center, m_radius, fillColor);
}

double CCircle::GetArea() const
{
	// m_pi ????? ????? ????????
	return std::atan(1) * 4 * m_radius * m_radius;
}

double CCircle::GetPerimeter() const
{
	return 2 * std::atan(1) * 4 * m_radius;
}

std::string CCircle::ToString() const
{
	std::string str("Type: " + m_name + "\n");
	str += PointToString(m_center, "Center");
	str += "Radius = " + std::to_string(m_radius) + "\n";
	return str;
}

CPoint CCircle::GetCenter() const
{
	return m_center;
}

double CCircle::GetRadius() const
{
	return m_radius;
}
