#include "CLineSegment.h"

CLineSegment::CLineSegment(const CPoint& startPoint, const CPoint& endPoint, uint32_t outlineColor)
	: CShape(outlineColor), m_startPoint(startPoint), m_endPoint(endPoint)
{}

CLineSegment::~CLineSegment()
{}

void CLineSegment::Draw(ICanvas& canvas) const
{
	auto lineColor = GetOutlineColor();

	canvas.DrawLine(m_startPoint, m_endPoint, lineColor);
}


double CLineSegment::GetArea() const
{
	return 0.0;
}

double CLineSegment::GetPerimeter() const
{
	return GetModule(m_startPoint, m_endPoint);
}

std::string CLineSegment::ToString() const
{
	std::string str("Type: " + m_name + "\n");
	str += PointToString(m_startPoint, "Start Point");
	str += PointToString(m_endPoint, "End Point");
	return str;
}

CPoint CLineSegment::GetStartPoint() const
{
	return m_startPoint;
}

CPoint CLineSegment::GetEndPoint() const
{
	return m_endPoint;
}
