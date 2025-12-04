#pragma once
#include "Point.h"

struct Frame
{
	Point LeftTop;
	Point RightBottom;

	Frame(const Point& leftTop, const Point& rightBottom) noexcept;
	Frame(const Point& leftTop, double size) noexcept;
	Frame(double x1, double y1, double x2, double y2) noexcept;

	double GetWidth() const;
	double GetHeight() const;
	bool IsEmpty() const;

	static Frame GetZeroFrame();
	void Extend(const Frame& other);
};