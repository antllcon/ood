#pragma once
#include <cmath>

struct RgbaColor
{
	double R = 0.0;
	double G = 0.0;
	double B = 0.0;
	double A = 1.0;

	bool operator==(const RgbaColor& other) const
	{
		constexpr double tolerance = 0.001;
		return std::abs(R - other.R) < tolerance && std::abs(G - other.G) < tolerance && std::abs(B - other.B) < tolerance && std::abs(A - other.A) < tolerance;
	}

	bool operator!=(const RgbaColor& other) const
	{
		return !(*this == other);
	}
};

struct Point
{
	double X = 0.0;
	double Y = 0.0;
};

struct Frame
{
	Point LeftTop;
	Point RightBottom;

	Frame(double x1, double y1, double x2, double y2)
		: LeftTop{x1, y1}
		, RightBottom{x2, y2}
	{
	}
};

struct LineStyle
{
	RgbaColor Color;
	double Width = 1.0;
	bool IsEnabled = true;

	bool operator==(const LineStyle& other) const
	{
		constexpr double tolerance = 0.001;
		return Color == other.Color && IsEnabled == other.IsEnabled && std::abs(Width - other.Width) < tolerance;
	}
};

struct FillStyle
{
	RgbaColor Color;
	bool IsEnabled = true;

	bool operator==(const FillStyle& other) const
	{
		return Color == other.Color && IsEnabled == other.IsEnabled;
	}
};