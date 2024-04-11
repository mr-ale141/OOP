#pragma once
#include <cstdint>
#include <vector>
#include <memory>
#include <iostream>
#include "CPoint.h"

class ICanvas
{
public:

	ICanvas(const ICanvas&) = delete;
	ICanvas& operator=(const ICanvas&) = delete;

	virtual void DrawLine(CPoint from, CPoint to, uint32_t lineColor) = 0;
	virtual void FillPolygon(std::vector<CPoint> points, uint32_t fillColor) = 0;
	virtual void DrawCircle(CPoint center, double radius, uint32_t lineColor) = 0;
	virtual void FillCircle(CPoint center, double radius, uint32_t fillColor) = 0;

	struct Deleter
	{
		void operator()(ICanvas* p) const { p->Delete(); }
	};

	friend struct ICanvas::Deleter;

	static std::unique_ptr<ICanvas, ICanvas::Deleter> CreateInstance();

protected:

	ICanvas() = default;
	virtual ~ICanvas() = 0;
	virtual void Delete();

};

ICanvas::~ICanvas() = default;

void ICanvas::Delete() { delete this; }

using CanvasPtr = std::unique_ptr<ICanvas, ICanvas::Deleter>;
