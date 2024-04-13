#pragma once
#include <fstream>
#include "ICanvas.h"

class CCanvas : public ICanvas
{
public:
	CCanvas(const std::string& fileName, int width, int height);
	~CCanvas();

	void DrawLine(CPoint from, CPoint to, uint32_t lineColor) override;
	void FillPolygon(std::vector<CPoint>& points, uint32_t fillColor) override;
	void DrawCircle(CPoint center, double radius, uint32_t lineColor) override;
	void FillCircle(CPoint center, double radius, uint32_t fillColor) override;

private:
	void WriteHeader();
	void WriteFooter();
	void WriteColor(uint32_t color);
	int m_width;
	int m_height;
	std::string m_fileName;
	std::ofstream m_file;
};
