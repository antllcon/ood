#pragma once

#include "ICanvas.h"

#include <iomanip>
#include <iostream>

class SvgCanvas : public ICanvas
{
public:
	explicit SvgCanvas(std::ostream& stream) : m_stream(stream)
	{
		m_stream << "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n";
		m_stream << std::fixed << std::setprecision(2);
	}

	~SvgCanvas() override
	{
		m_stream << "</svg>\n";
	}

	void DrawLine(Point p1, Point p2) override
	{
		m_stream << "<line x1=\"" << p1.X << "\" y1=\"" << p1.Y
				 << "\" x2=\"" << p2.X << "\" y2=\"" << p2.Y << "\" "
				 << GetStrokeAttrs() << " />\n";
	}

	void DrawEllipse(Point center, double rx, double ry) override
	{
		m_stream << "<ellipse cx=\"" << center.X << "\" cy=\"" << center.Y
				 << "\" rx=\"" << rx << "\" ry=\"" << ry << "\" "
				 << GetStrokeAttrs() << " fill=\"none\" />\n";
	}

	void FillEllipse(Point center, double rx, double ry) override
	{
		m_stream << "<ellipse cx=\"" << center.X << "\" cy=\"" << center.Y
				 << "\" rx=\"" << rx << "\" ry=\"" << ry << "\" "
				 << GetFillAttrs() << " />\n";
	}

	void FillPolygon(const std::vector<Point>& points) override
	{
		if (points.empty()) return;
		m_stream << "<polygon points=\"";
		for (const auto& [X, Y] : points)
		{
			m_stream << X << "," << Y << " ";
		}
		m_stream << "\" " << GetFillAttrs() << " />\n";
	}

	void SetFillColor(RgbaColor color) override
	{
		m_fillColor = color;
	}

	void SetStrokeColor(RgbaColor color) override
	{
		m_strokeColor = color;
	}

	void SetStrokeWidth(double width) override
	{
		m_strokeWidth = width;
	}

private:
	static std::string FmtColor(const RgbaColor& c)
	{
		std::ostringstream oss;
		oss << "rgba(" << static_cast<int>(c.R) << "," << static_cast<int>(c.G) << "," << static_cast<int>(c.B) << "," << c.A << ")";
		return oss.str();
	}

	std::string GetStrokeAttrs() const
	{
		std::ostringstream oss;
		oss << "stroke=\"" << FmtColor(m_strokeColor) << "\" stroke-width=\"" << m_strokeWidth << "\"";
		return oss.str();
	}

	std::string GetFillAttrs() const
	{
		std::ostringstream oss;
		oss << "fill=\"" << FmtColor(m_fillColor) << "\"";
		return oss.str();
	}

	std::ostream& m_stream;
	RgbaColor m_fillColor;
	RgbaColor m_strokeColor;
	double m_strokeWidth = 1.0;
};