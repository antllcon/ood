#pragma once
#include <cmath>

namespace
{
constexpr double TOLERANCE = 0.001;

bool AreComponentsEqual(double c1, double c2) noexcept
{
	return std::abs(c1 - c2) < TOLERANCE;
}
} // namespace

struct RgbColor
{
	double r = 0.0;
	double g = 0.0;
	double b = 0.0;

	bool operator==(const RgbColor& other) const
	{
		return AreComponentsEqual(r, other.r) &&
			   AreComponentsEqual(g, other.g) &&
			   AreComponentsEqual(b, other.b);
	}

	bool operator!=(const RgbColor& other) const
	{
		return !(*this == other);
	}
};

struct RgbaColor : RgbColor
{
	double a = 1.0;

	bool operator==(const RgbaColor& other) const
	{
		return RgbColor::operator==(other) && AreComponentsEqual(a, other.a);
	}

	bool operator!=(const RgbaColor& other) const
	{
		return !(*this == other);
	}
};