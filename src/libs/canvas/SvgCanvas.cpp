#include "SvgCanvas.h"

#include <fstream>
#include <iomanip>

namespace
{
std::string RgbaToSvg(const RgbaColor& color)
{
	int r = static_cast<int>(color.r * 255);
	int g = static_cast<int>(color.g * 255);
	int b = static_cast<int>(color.b * 255);

	std::stringstream ss;
	ss << "rgb(" << r << "," << g << "," << b << ")";
	return ss.str();
}
} // namespace

void SvgCanvas::SetFillColor(RgbaColor color)
{
	m_fillColor = color;
}

void SvgCanvas::SetStrokeColor(RgbaColor color)
{
	m_strokeColor = color;
}

void SvgCanvas::SetStrokeWidth(double width)
{
	m_strokeWidth = width;
}

SvgCanvas::SvgCanvas(double width, double height)
	: m_width(width)
	, m_height(height)
{
	m_strokeColor = {0, 0, 0, 1};
	m_fillColor = {1, 1, 1, 1};
	m_strokeWidth = 1.0;
}

SvgCanvas::~SvgCanvas()
{
	Save("save.svg");
}

void SvgCanvas::DrawLine(Point p1, Point p2)
{
	m_stream << "<line x1=\"" << p1.x << "\" y1=\"" << p1.y
			 << "\" x2=\"" << p2.x << "\" y2=\"" << p2.y << "\" "
			 << "stroke=\"" << RgbaToSvg(m_strokeColor) << "\" "
			 << "stroke-opacity=\"" << m_strokeColor.a << "\" "
			 << "stroke-width=\"" << m_strokeWidth << "\" />\n";
}

void SvgCanvas::DrawEllipse(Point center, double rx, double ry)
{
	m_stream << "<ellipse cx=\"" << center.x << "\" cy=\"" << center.y
			 << "\" rx=\"" << rx << "\" ry=\"" << ry << "\" "
			 << "stroke=\"" << RgbaToSvg(m_strokeColor) << "\" "
			 << "stroke-opacity=\"" << m_strokeColor.a << "\" "
			 << "stroke-width=\"" << m_strokeWidth << "\" "
			 << "fill=\"none\" />\n";
}

void SvgCanvas::FillEllipse(Point center, double rx, double ry)
{
	m_stream << "<ellipse cx=\"" << center.x << "\" cy=\"" << center.y
			 << "\" rx=\"" << rx << "\" ry=\"" << ry << "\" "
			 << "fill=\"" << RgbaToSvg(m_fillColor) << "\" "
			 << "fill-opacity=\"" << m_fillColor.a << "\" "
			 << "stroke=\"none\" />\n";
}

void SvgCanvas::FillPolygon(const std::vector<Point>& points)
{
	if (points.empty()) return;

	m_stream << "<polygon points=\"";
	for (size_t i = 0; i < points.size(); ++i)
	{
		m_stream << points[i].x << "," << points[i].y;
		if (i < points.size() - 1) m_stream << " ";
	}
	m_stream << "\" "
			 << "fill=\"" << RgbaToSvg(m_fillColor) << "\" "
			 << "fill-opacity=\"" << m_fillColor.a << "\" "
			 << "stroke=\"none\" />\n";
}

void SvgCanvas::Save(const std::string& filepath) const
{
	std::ofstream file(filepath);

	if (!file.is_open())
	{
		throw std::runtime_error("Failed to open file for writing: " + filepath);
	}

	file << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n";
	file << "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" "
		 << "width=\"" << m_width << "\" height=\"" << m_height << "\">\n";

	file << m_stream.str();

	file << "</svg>";
}