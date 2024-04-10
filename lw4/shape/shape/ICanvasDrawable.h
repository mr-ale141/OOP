#pragma once
#include "ICanvas.h"

class ICanvasDrawable
{
public:
	virtual void Draw(ICanvas canvas) = 0;
	ICanvasDrawable(const ICanvasDrawable&) = delete;
	ICanvasDrawable& operator=(const ICanvasDrawable&) = delete;

	struct Deleter
	{
		void operator()(ICanvasDrawable* p) const { p->Delete(); }
	};

protected:
	ICanvasDrawable() = default;
	virtual ~ICanvasDrawable() = 0;
	virtual void Delete();
};

ICanvasDrawable::~ICanvasDrawable() = default;

void ICanvasDrawable::Delete() { delete this; }