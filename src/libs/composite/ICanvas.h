#pragma once
#include <vector>
#include "Common.h"

class ICanvas
{
public:
	virtual ~ICanvas() = default;

	virtual void DrawLine(Point p1, Point p2) = 0;
	virtual void DrawEllipse(Point center, double rx, double ry) = 0;
	virtual void FillEllipse(Point center, double rx, double ry) = 0;
	virtual void FillPolygon(const std::vector<Point>& points) = 0;
	virtual void SetFillColor(RgbaColor color) = 0;
	virtual void SetStrokeColor(RgbaColor color) = 0;
	virtual void SetStrokeWidth(double width) = 0;
};