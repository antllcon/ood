#ifndef SVGCANVAS_H
#define SVGCANVAS_H

#include "ICanvas.h"
#include <string>

constexpr size_t SVGCANVAS_WIDTH = 800;
constexpr size_t SVGCANVAS_HEIGHT = 600;

class SvgCanvas final : public ICanvas
{
public:
	explicit SvgCanvas(const std::string& filename, double width = SVGCANVAS_WIDTH, double height = SVGCANVAS_HEIGHT);
	~SvgCanvas() override;
	void SetColor(Color color) override;
	void MoveTo(double x, double y) override;
	void LineTo(double x, double y) override;
	void DrawEllipse(Point center, double rx, double ry) override;
	void DrawText(double left, double top, double fontSize, const std::string& text) override;
	void SaveToFile();

private:
	std::string m_filename;
	double m_width;
	double m_height;
	Color m_currentColor;
	std::string m_svgContent;
	double m_currentX;
	double m_currentY;
	bool m_hasCurrentPoint;
};

#endif // SVGCANVAS_H