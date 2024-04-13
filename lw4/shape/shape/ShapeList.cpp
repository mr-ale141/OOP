#include "ShapeList.h"
#include <algorithm>
#include <iomanip>

namespace
{
	void ToLower(std::string& str)
	{
		std::transform(str.begin(), str.end(), str.begin(),
			[](unsigned char c) { return std::tolower(c); });
	}
}

ShapeList::ShapeList(const std::string& fileName, int width, int height)
	: m_canvas(fileName, width, height)
{
	std::cout << "Enter '?' for help." << std::endl;
}

bool ShapeList::Add(std::stringstream& ss)
{
	bool res = false;

	std::string word;

	ss >> word;

	ToLower(word);

	if (word == "rectangle")
		res = AddRectangle(ss);
	else if (word == "triangle")
		res = AddTriangle(ss);
	else if (word == "circle")
		res = AddCircle(ss);
	else if (word == "linesegment")
		res = AddLine(ss);
	else if (word == "?")
	{
		ShowHelp();
		res = true;
	}

	auto drowableShape = std::dynamic_pointer_cast<ICanvasDrawable>(m_shapes.back());

	drowableShape->Draw(m_canvas);

	return res;
}

ShapePtr ShapeList::GetMinArea() const
{
	return m_minArea;
}

ShapePtr ShapeList::GetMinPerimeter() const
{
	return m_minPerimeter;
}

bool ShapeList::AddRectangle(std::stringstream& ss)
{
	CPoint topLeft;
	double width{};
	double height{};
	uint32_t lineColor{};
	uint32_t fillColor{};

	if (!(ss >> topLeft.m_x))
		return false;

	if (!(ss >> topLeft.m_y))
		return false;

	if (!(ss >> width))
		return false;

	if (!(ss >> height))
		return false;

	ss >> std::hex;

	if (!(ss >> lineColor))
		return false;

	if (!(ss >> fillColor))
		return false;

	ss >> std::dec;

	auto newShape = std::make_shared<CRectangle>(topLeft, width, height, lineColor, fillColor);

	UpdateMinArea(newShape);
	UpdateMinPerimeter(newShape);

	m_shapes.emplace_back(newShape);

	return true;
}

bool ShapeList::AddTriangle(std::stringstream& ss)
{
	CPoint v1;
	CPoint v2;
	CPoint v3;
	uint32_t lineColor{};
	uint32_t fillColor{};

	if (!(ss >> v1.m_x))
		return false;

	if (!(ss >> v1.m_y))
		return false;

	if (!(ss >> v2.m_x))
		return false;

	if (!(ss >> v2.m_y))
		return false;

	if (!(ss >> v3.m_x))
		return false;

	if (!(ss >> v3.m_y))
		return false;

	ss >> std::hex;

	if (!(ss >> lineColor))
		return false;

	if (!(ss >> fillColor))
		return false;

	ss >> std::dec;

	auto newShape = std::make_shared<CTriangle>(v1, v2, v3, lineColor, fillColor);

	UpdateMinArea(newShape);
	UpdateMinPerimeter(newShape);

	m_shapes.emplace_back(newShape);

	return true;
}

bool ShapeList::AddCircle(std::stringstream& ss)
{
	CPoint center;
	double radius{};
	uint32_t lineColor{};
	uint32_t fillColor{};

	if (!(ss >> center.m_x))
		return false;

	if (!(ss >> center.m_y))
		return false;

	if (!(ss >> radius))
		return false;

	ss >> std::hex;

	if (!(ss >> lineColor))
		return false;

	if (!(ss >> fillColor))
		return false;

	ss >> std::dec;

	auto newShape = std::make_shared<CCircle>(center, radius, lineColor, fillColor);

	UpdateMinArea(newShape);
	UpdateMinPerimeter(newShape);

	m_shapes.emplace_back(newShape);

	return true;
}

bool ShapeList::AddLine(std::stringstream& ss)
{
	CPoint start;
	CPoint end;
	uint32_t lineColor{};

	if (!(ss >> start.m_x))
		return false;

	if (!(ss >> start.m_y))
		return false;

	if (!(ss >> end.m_x))
		return false;

	if (!(ss >> end.m_y))
		return false;

	ss >> std::hex;

	if (!(ss >> lineColor))
		return false;

	ss >> std::dec;

	auto newShape = std::make_shared<CLineSegment>(start, end, lineColor);

	UpdateMinPerimeter(newShape);

	m_shapes.emplace_back(newShape);

	return true;
}

void ShapeList::ShowHelp()
{
	std::cout << "Examples:" << std::endl;
	std::cout << "Add Rectangle  : Rectangle <TopLeft.x> <TopLeft.y> <Width> <Height> <LineColor> <FillColor>" << std::endl;
	std::cout << "Add Triangle   : Triangle <V1.x> <V1.y> <V2.x> <V2.y> <V3.x> <V3.y> <LineColor> <FillColor>" << std::endl;
	std::cout << "Add Circle     : Circle <Center.x> <Center.y> <Radius> <LineColor> <FillColor>" << std::endl;
	std::cout << "Add LineSegment: LineSegment <Start.x> <Start.y> <End.x> <End.y> <LineColor>" << std::endl;
}

void ShapeList::UpdateMinArea(ShapePtr shape)
{
	if (!shape->GetArea())
		return;

	if (!m_minArea)
		m_minArea = shape;
	else if (shape->GetArea() < m_minArea->GetArea())
		m_minArea = shape;
}

void ShapeList::UpdateMinPerimeter(ShapePtr shape)
{
	if (!m_minPerimeter)
		m_minPerimeter = shape;
	else if (shape->GetArea() < m_minPerimeter->GetArea())
		m_minPerimeter = shape;
}

void ShapeList::ShowShape(ShapePtr shape)
{
	if (!shape)
		return;

	auto iShape = std::dynamic_pointer_cast<IShape>(shape);

	std::cout << "Area = " << iShape->GetArea() << std::endl;

	std::cout << "Perimeter = " << iShape->GetPerimeter() << std::endl;

	std::cout << std::hex;

	std::cout << "Outline color = ";
	std::cout << std::setfill('0') << std::setw(6);
	std::cout << iShape->GetOutlineColor() << std::endl;

	auto iSolidShape = std::dynamic_pointer_cast<ISolidShape>(iShape);

	if (iSolidShape)
	{
		std::cout << "Fill color = ";
		std::cout << std::setfill('0') << std::setw(6);
		std::cout << iSolidShape->GetFillColor() << std::endl;
	}

	std::cout << std::dec;

	std::cout << iShape->ToString();
}
