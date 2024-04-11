#include "CCanvas.h"

CCanvas::CCanvas()
{

}

CCanvas::~CCanvas()
{

}

void CCanvas::DrawLine(CPoint from, CPoint to, uint32_t lineColor)
{

}

void CCanvas::FillPolygon(std::vector<CPoint> points, uint32_t fillColor)
{

}

void CCanvas::DrawCircle(CPoint center, double radius, uint32_t lineColor)
{

}

void CCanvas::FillCircle(CPoint center, double radius, uint32_t fillColor)
{

}

CanvasPtr ICanvas::CreateInstance()
{
	return CanvasPtr(new CCanvas());
}
