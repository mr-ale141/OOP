#pragma once
#include "CCanvas.h"
#include "CTriangle.h"
#include "CRectangle.h"
#include "CCircle.h"
#include "CLineSegment.h"
#include <sstream>

using ShapePtr = std::shared_ptr<IShape>;

class ShapeList
{
public:
	explicit ShapeList(const std::string& fileName, int width = 800, int height = 600);
	bool Add(std::stringstream& ss);
	ShapePtr GetMinArea() const;
	ShapePtr GetMinPerimeter() const;
	static void ShowShape(ShapePtr shape);
	static void ShowHelp();
	void ChangeCanvasI(ICanvas* newCanvas);

protected:
	bool AddTriangle(std::stringstream& ss);
	bool AddRectangle(std::stringstream& ss);
	bool AddCircle(std::stringstream& ss);
	bool AddLine(std::stringstream& ss);
	void UpdateMinArea(ShapePtr shape);
	void UpdateMinPerimeter(ShapePtr shape);

private:
	std::vector<ShapePtr> m_shapes;
	ShapePtr m_minArea = nullptr;
	ShapePtr m_minPerimeter = nullptr;
	CCanvas m_canvas;
	ICanvas* m_mockCanvas = nullptr;
};
