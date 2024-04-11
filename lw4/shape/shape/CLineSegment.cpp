#include "CLineSegment.h"

CLineSegment::CLineSegment(const CPoint& startPoint, const CPoint& endPoint, uint32_t outlineColor)
	: m_startPoint(startPoint), m_endPoint(endPoint), m_outlineColor(outlineColor)
{}

CLineSegment::~CLineSegment()
{}

void CLineSegment::Draw(ICanvas& canvas) const
{
	std::cout << "not now" << std::endl;
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
	return std::string("Line Segment");
}

uint32_t CLineSegment::GetOutlineColor() const
{

}

CPoint CLineSegment::GetStartPoint() const
{

}

CPoint CLineSegment::GetEndPoint() const
{

}

ShapePtr CLineSegment::CreateInstance(const CPoint& startPoint, const CPoint& endPoint, uint32_t outlineColor)
{
	return ShapePtr(new CLineSegment(startPoint, endPoint, outlineColor));
}
