#include "CCanvas.h"
#include <exception>
#include <iomanip>

CCanvas::CCanvas(const std::string& fileName, int width, int height) 
	: m_width(width), m_height(height), m_fileName(fileName)
{
	m_file.open(m_fileName, std::fstream::out | std::fstream::trunc);
	if (!m_file.is_open())
		throw std::invalid_argument("ERROR! Can't create file '" + m_fileName + "'");

	WriteHeader();
}

CCanvas::~CCanvas()
{
	WriteFooter();
	m_file.flush();
	m_file.close();
}

void CCanvas::DrawLine(CPoint from, CPoint to, uint32_t lineColor)
{
	m_file << '\t'
		<< "<line x1 = '"
		<< from.m_x
		<< "' y1 = '"
		<< from.m_y
		<< "' x2 = '"
		<< to.m_x
		<< "' y2 = '"
		<< to.m_y
		<< "' stroke = '";

	WriteColor(lineColor);

	m_file << "' />\n";
}

void CCanvas::FillPolygon(std::vector<CPoint>& points, uint32_t fillColor)
{
	m_file << '\t'
		<< "<polygon points='";

	auto size = points.size();
	for (auto& point : points)
	{
		size--;
		m_file << point.m_x << ',' << point.m_y;
		if (size)
			m_file << ' ';
	}

	m_file << "' fill = '";
	WriteColor(fillColor);
	m_file << "' />\n";
}

void CCanvas::DrawCircle(CPoint center, double radius, uint32_t lineColor)
{
	m_file << '\t'
		<< "<circle cx = '"
		<< center.m_x
		<< "' cy = '"
		<< center.m_y
		<< "' r = '"
		<< (int)radius
		<< "' stroke = '";
	WriteColor(lineColor);
	m_file << "' fill = 'none' />\n";
}

void CCanvas::FillCircle(CPoint center, double radius, uint32_t fillColor)
{
	m_file << '\t'
		<< "<circle cx = '"
		<< center.m_x
		<< "' cy = '"
		<< center.m_y
		<< "' r = '"
		<< (int)radius
		<< "' stroke = 'none' "
		<< "fill = '";
	WriteColor(fillColor);
	m_file << "' />\n";
}

void CCanvas::WriteHeader()
{
	m_file 
		<< "<svg xmlns=\"http://www.w3.org/2000/svg\" width='" 
		<< m_width
		<< "' height='"
		<< m_height
		<< "'>\n";
}

void CCanvas::WriteFooter()
{
	m_file << "</svg>\n";
}

void CCanvas::WriteColor(uint32_t color)
{
	m_file << '#' << std::hex << std::setfill('0') << std::setw(6) << color << std::dec;
}
