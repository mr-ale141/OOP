#include "CCircle.h"

CCircle::CCircle(
	const CPoint& center, 
	double radius,
	uint32_t outlineColor,
	uint32_t fillColor
)
	: 
	m_center(center), m_radius(radius), 
	m_outlineColor(outlineColor), m_fillColor(fillColor)
{}

CCircle::~CCircle()
{}

void CCircle::Draw(ICanvas& canvas) const
{
	std::cout << "not now" << std::endl;
}

double CCircle::GetArea() const
{

}

double CCircle::GetPerimeter() const
{


}

std::string CCircle::ToString() const
{

}

uint32_t CCircle::GetOutlineColor() const
{

}

uint32_t CCircle::GetFillColor() const
{

}

CPoint CCircle::GetCenter() const
{

}

double CCircle::GetRadius() const
{

}

ShapePtr CCircle::CreateInstance(
	const CPoint& center, 
	double radius,
	uint32_t outlineColor,
	uint32_t fillColor
)
{
	return ShapePtr(new CCircle(center, radius, outlineColor, fillColor));
}
