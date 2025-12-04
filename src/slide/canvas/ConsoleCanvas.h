#pragma once
#include "ICanvas.h"
#include "common/Color.h"
#include "common/Point.h"

#include <string>

class ConsoleCanvas final : public ICanvas
{
public:
	void DrawLine(Point p1, Point p2) override;
	void DrawEllipse(Point center, double rx, double ry) override;

	void FillEllipse(Point center, double rx, double ry) override;
	void FillPolygon(const std::vector<Point>& points) override;

	void SetFillColor(RgbaColor color) override;
	void SetStrokeColor(RgbaColor color) override;
	void SetStrokeWidth(double width) override;

private:
	static void PrintColor(const std::string& prefix, const RgbaColor& color);
};