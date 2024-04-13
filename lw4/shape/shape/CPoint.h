#pragma once

class CPoint
{
public:
	CPoint() = default;
	CPoint(double x, double y) : m_x(x), m_y(y) {}

	CPoint operator-(const CPoint& p) const { return CPoint(m_x - p.m_x, m_y - p.m_y); }
	CPoint operator+(const CPoint& p) const { return CPoint(m_x + p.m_x, m_y + p.m_y); }

	double m_x = 0.0;
	double m_y = 0.0;
};
