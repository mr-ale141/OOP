#pragma once
#include "ISolidShape.h"
#include "CShape.h"

class CSolidShape : public ISolidShape
{
public:
	virtual ~CSolidShape() = default;
	
	//getOutline ????????????? ?? Hollow
	uint32_t GetOutlineColor() const final;
	uint32_t GetFillColor() const final;

protected:
	CSolidShape(uint32_t outlineColor, uint32_t fillColor);

private:
	uint32_t m_outlineColor;
	uint32_t m_fillColor;
};
