#include "SvgCanvas.h"

#include <fstream>
#include <iostream>

SvgCanvas::SvgCanvas(const std::string& filename, const double width, const double height)
	: m_filename(filename)
	, m_width(width)
	, m_height(height)
	, m_currentColor(0, 0, 0)
	, m_currentX(0)
	, m_currentY(0)
	, m_hasCurrentPoint(false)
{
	// Начало SVG документа
	m_svgContent = R"(<?xml version="1.0" encoding="UTF-8"?>
<svg width=")"
		+ std::to_string(width) + R"(" height=")" + std::to_string(height) + R"("
     xmlns="http://www.w3.org/2000/svg">
)";
}

SvgCanvas::~SvgCanvas()
{
	SaveToFile();
}

void SvgCanvas::SetColor(const Color color)
{
	m_currentColor = color;
}

void SvgCanvas::MoveTo(const double x, const double y)
{
	m_currentX = x;
	m_currentY = y;
	m_hasCurrentPoint = true;
}

void SvgCanvas::LineTo(const double x, const double y)
{
	if (m_hasCurrentPoint)
	{
		const std::string colorStr = m_currentColor.ToString();
		m_svgContent += R"(<line x1=")" + std::to_string(m_currentX) + R"(" y1=")" + std::to_string(m_currentY) + R"(" x2=")" + std::to_string(x) + R"(" y2=")" + std::to_string(y) + R"(" stroke=")" + colorStr + R"(" />
)";
	}

	m_currentX = x;
	m_currentY = y;
	m_hasCurrentPoint = true;
}

void SvgCanvas::DrawEllipse(const Point center, double rx, double ry)
{
	if (rx < 0)
	{
		rx = -rx;
	}

	if (ry < 0)
	{
		ry = -ry;
	}

	const std::string color = m_currentColor.ToString();
	m_svgContent += R"(<ellipse cx=")" + std::to_string(center.x) + R"(" cy=")" + std::to_string(center.y) + R"(" rx=")" + std::to_string(rx) + R"(" ry=")" + std::to_string(ry) + R"(" fill=")" + color + R"(" />
)";
}

void SvgCanvas::DrawText(const double left, const double top, const double fontSize, const std::string& text)
{
	const std::string color = m_currentColor.ToString();
	m_svgContent += R"(<text x=")" + std::to_string(left) + R"(" y=")" + std::to_string(top) + R"(" font-size=")" + std::to_string(fontSize) + R"(" fill=")" + color + R"(">)" + text + R"(</text>
)";
}

void SvgCanvas::SaveToFile()
{
	m_svgContent += "</svg>\n";

	std::ofstream file(m_filename);
	if (file.is_open())
	{
		file << m_svgContent;
		file.close();
		std::cout << "SVG saved to: " << m_filename << std::endl;
	}
	else
	{
		std::cerr << "Error: Cannot open file " << m_filename << std::endl;
	}
}