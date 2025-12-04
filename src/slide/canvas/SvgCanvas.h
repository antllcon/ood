#pragma once
#include "ICanvas.h"

#include <sstream>
#include <string>
#include <vector>

class SvgCanvas final : public ICanvas
{
public:
	SvgCanvas(double width, double height);
	~SvgCanvas() override;

	void DrawLine(Point p1, Point p2) override;
	void DrawEllipse(Point center, double rx, double ry) override;

	void FillEllipse(Point center, double rx, double ry) override;
	void FillPolygon(const std::vector<Point>& points) override;

	void SetFillColor(RgbaColor color) override;
	void SetStrokeColor(RgbaColor color) override;
	void SetStrokeWidth(double width) override;
	void Save(const std::string& filepath) const;

private:
	double m_width;
	double m_height;

	RgbaColor m_strokeColor;
	RgbaColor m_fillColor;
	double m_strokeWidth;

	std::stringstream m_stream;
};