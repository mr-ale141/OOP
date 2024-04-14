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
		return true;
	}

	if (res == true)
	{
		auto drowableShape = std::dynamic_pointer_cast<ICanvasDrawable>(m_shapes.back());
		if (m_mockCanvas == nullptr)
			drowableShape->Draw(m_canvas);
		else
			drowableShape->Draw(*m_mockCanvas);
	}

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

	int maxX = m_canvas.m_width;
	int maxY = m_canvas.m_height;

	if (!(ss >> topLeft.m_x) || topLeft.m_x < 0 || topLeft.m_x > maxX)
		return false;

	if (!(ss >> topLeft.m_y) || topLeft.m_y < 0 || topLeft.m_y > maxY)
		return false;

	if (!(ss >> width) || width < 0 || width > maxX)
		return false;

	if (!(ss >> height) || height < 0 || height > maxX)
		return false;

	ss >> std::hex;

	if (!(ss >> lineColor) || lineColor < 0 || lineColor > 0xffffff)
		return false;

	if (!(ss >> fillColor) || fillColor < 0 || fillColor > 0xffffff)
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

	int maxX = m_canvas.m_width;
	int maxY = m_canvas.m_height;

	if (!(ss >> v1.m_x) || v1.m_x < 0 || v1.m_x > maxX)
		return false;

	if (!(ss >> v1.m_y) || v1.m_y < 0 || v1.m_y > maxY)
		return false;

	if (!(ss >> v2.m_x) || v2.m_x < 0 || v2.m_x > maxX)
		return false;

	if (!(ss >> v2.m_y) || v2.m_y < 0 || v2.m_y > maxY)
		return false;

	if (!(ss >> v3.m_x) || v3.m_x < 0 || v3.m_x > maxX)
		return false;

	if (!(ss >> v3.m_y) || v3.m_y < 0 || v3.m_y > maxY)
		return false;

	ss >> std::hex;

	if (!(ss >> lineColor) || lineColor < 0 || lineColor > 0xffffff)
		return false;

	if (!(ss >> fillColor) || fillColor < 0 || fillColor > 0xffffff)
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

	int maxX = m_canvas.m_width;
	int maxY = m_canvas.m_height;

	if (!(ss >> center.m_x) || center.m_x < 0 || center.m_x > maxX)
		return false;

	if (!(ss >> center.m_y) || center.m_y < 0 || center.m_y > maxY)
		return false;

	if (!(ss >> radius) || radius < 0 || radius > maxX)
		return false;

	ss >> std::hex;

	if (!(ss >> lineColor) || lineColor < 0 || lineColor > 0xffffff)
		return false;

	if (!(ss >> fillColor) || fillColor < 0 || fillColor > 0xffffff)
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

	int maxX = m_canvas.m_width;
	int maxY = m_canvas.m_height;

	if (!(ss >> start.m_x) || start.m_x < 0 || start.m_x > maxX)
		return false;

	if (!(ss >> start.m_y) || start.m_y < 0 || start.m_y > maxY)
		return false;

	if (!(ss >> end.m_x) || end.m_x < 0 || end.m_x > maxX)
		return false;

	if (!(ss >> end.m_y) || end.m_y < 0 || end.m_y > maxY)
		return false;

	ss >> std::hex;

	if (!(ss >> lineColor) || lineColor < 0 || lineColor > 0xffffff)
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
	else if (shape->GetPerimeter() < m_minPerimeter->GetPerimeter())
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

void ShapeList::ChangeCanvasI(ICanvas* mock)
{
	m_mockCanvas = mock;
}