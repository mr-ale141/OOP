#include "CRectangle.h"

CRectangle::CRectangle(
	const CPoint& leftTop,
	const CPoint& rightBottom,
	double width,
	double height,
	uint32_t outlineColor,
	uint32_t fillColor
)
	:
	m_leftTop(leftTop), m_rightBottom(rightBottom), m_width(width),
	m_height(height), m_outlineColor(outlineColor), m_fillColor(fillColor)
{}

CRectangle::~CRectangle()
{}

void CRectangle::Draw(ICanvas& canvas) const
{
	std::cout << "not now" << std::endl;
}

double CRectangle::GetArea() const
{

}

double CRectangle::GetPerimeter() const
{

}

std::string CRectangle::ToString() const
{

}

uint32_t CRectangle::GetOutlineColor() const
{

}

uint32_t CRectangle::GetFillColor() const
{

}

CPoint CRectangle::GetLeftTop() const
{

}

CPoint CRectangle::GetRightBottom() const
{

}

double CRectangle::GetWidth() const
{

}

double CRectangle::GetHeight() const
{

}

ShapePtr CRectangle::CreateInstance(
	const CPoint& leftTop,
	const CPoint& rightBottom,
	double width,
	double height,
	uint32_t outlineColor,
	uint32_t fillColor
)
{
	return ShapePtr(new CRectangle(
		leftTop,
		rightBottom,
		width,
		height,
		outlineColor,
		fillColor
	));
}
