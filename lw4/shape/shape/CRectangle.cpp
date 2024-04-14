#include "CRectangle.h"

CRectangle::CRectangle(
	const CPoint& leftTop,
	double width,
	double height,
	uint32_t outlineColor,
	uint32_t fillColor
)
	: CSolidShape(outlineColor, fillColor),
	m_leftTop(leftTop), m_width(width), m_height(height)
{}

void CRectangle::Draw(ICanvas& canvas) const
{
	auto lineColor = GetOutlineColor();
	auto fillColor = GetFillColor();

	CPoint topR(m_leftTop.m_x + m_width, m_leftTop.m_y);
	CPoint bottomL(m_leftTop.m_x, m_leftTop.m_y + m_height);
	CPoint bottomR(m_leftTop.m_x + m_width, m_leftTop.m_y + m_height);

	canvas.DrawLine(m_leftTop, topR, lineColor);
	canvas.DrawLine(topR, bottomR, lineColor);
	canvas.DrawLine(bottomR, bottomL, lineColor);
	canvas.DrawLine(bottomL, m_leftTop, lineColor);

	std::vector<CPoint> points{ m_leftTop, topR, bottomR, bottomL };

	canvas.FillPolygon(points, fillColor);
}

double CRectangle::GetArea() const
{
	return m_width * m_height;
}

double CRectangle::GetPerimeter() const
{
	return 2 * m_width + 2 * m_height;
}

std::string CRectangle::ToString() const
{
	std::string str("Type: " + m_name + "\n");
	str += PointToString(m_leftTop, "Left Top");
	str += "Width = " + std::to_string(m_width) + "\n";
	str += "Height = " + std::to_string(m_height) + "\n";
	return str;
}

CPoint CRectangle::GetLeftTop() const
{
	return m_leftTop;
}

CPoint CRectangle::GetRightBottom() const
{
	return CPoint(m_leftTop.m_x + m_width, m_leftTop.m_y + m_height);
}

double CRectangle::GetWidth() const
{
	return m_width;
}

double CRectangle::GetHeight() const
{
	return m_height;
}
