#ifndef ICANVAS_H
#define ICANVAS_H

#include "Color/Color.h"
#include "Point.h"

class ICanvas
{
	public:
	virtual ~ICanvas() = default;
	virtual void SetColor(Color color) = 0;
	virtual void MoveTo(double x, double y) = 0;
	virtual void LineTo(double x, double y) = 0;
	virtual void DrawEllipse(Point center, double rx, double ry) = 0;
	virtual void DrawText(double left, double top, double fontSize, const std::string& text) = 0;
};

#endif // ICANVAS_H