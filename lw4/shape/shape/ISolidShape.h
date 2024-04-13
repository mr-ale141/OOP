#pragma once
#include "IShape.h"

class ISolidShape : public IShape
{
public:
	virtual ~ISolidShape() = default;

	//uint32_t GetOutlineColor() const final { return 0; };
	virtual uint32_t GetFillColor() const = 0;

protected:
	ISolidShape() = default;
};
