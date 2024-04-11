#pragma once
#include "ICanvas.h"



class ICanvasDrawable
{
public:

	ICanvasDrawable(const ICanvasDrawable&) = delete;
	ICanvasDrawable& operator=(const ICanvasDrawable&) = delete;

	virtual void Draw(ICanvas& canvas) const = 0;

	struct Deleter
	{
		void operator()(ICanvasDrawable* p) const { p->Delete(); }
	};

	friend struct ICanvasDrawable::Deleter;

protected:

	ICanvasDrawable() = default;
	virtual ~ICanvasDrawable() = 0;
	virtual void Delete();

};

ICanvasDrawable::~ICanvasDrawable() = default;

void ICanvasDrawable::Delete() { delete this; }
