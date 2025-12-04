#include "ConsoleCanvas.h"
#include <iomanip>
#include <iostream>

void ConsoleCanvas::PrintColor(const std::string& prefix, const RgbaColor& color)
{
	std::cout << prefix << "("
			  << "R:" << std::fixed << std::setprecision(2) << color.r
			  << ", G:" << color.g
			  << ", B:" << color.b
			  << ", A:" << color.a << ")";
}

void ConsoleCanvas::SetFillColor(RgbaColor color)
{
	PrintColor("Set fill color ", color);
	std::cout << std::endl;
}

void ConsoleCanvas::SetStrokeColor(RgbaColor color)
{
	PrintColor("Set stroke color ", color);
	std::cout << std::endl;
}

void ConsoleCanvas::SetStrokeWidth(double width)
{
	std::cout << "Set stroke width (" << std::fixed << std::setprecision(2) << width << ")" << std::endl;
}

void ConsoleCanvas::DrawLine(Point p1, Point p2)
{
	std::cout << "Draw line (" << p1.x << "," << p1.y << " -> " << p2.x << "," << p2.y << ")" << std::endl;
}

void ConsoleCanvas::DrawEllipse(Point center, double rx, double ry)
{
	std::cout << "Draw ellipse (Center:" << center.x << "," << center.y
			  << ", rx:" << rx << ", ry:" << ry << ")" << std::endl;
}

void ConsoleCanvas::FillEllipse(Point center, double rx, double ry)
{
	std::cout << "Fill ellipse (Center:" << center.x << "," << center.y
			  << ", rx:" << rx << ", ry:" << ry << ")" << std::endl;
}

void ConsoleCanvas::FillPolygon(const std::vector<Point>& points)
{
	std::cout << "Fill polygon (";
	for (size_t i = 0; i < points.size(); ++i)
	{
		std::cout << "(" << points[i].x << "," << points[i].y << ")";
		if (i < points.size() - 1)
		{
			std::cout << ", ";
		}
	}
	std::cout << ")" << std::endl;
}