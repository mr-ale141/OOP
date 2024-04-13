#pragma once
#include "IShape.h"

class CShape : public IShape 
{
public:
	virtual ~CShape() = default;

	uint32_t GetOutlineColor() const final;

protected:
	CShape(uint32_t outlineColor);

private:
	uint32_t m_outlineColor;
};
