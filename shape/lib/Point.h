#ifndef POINT_H
#define POINT_H

#include <math.h>

struct Point
{
	double x;
	double y;
};

inline double GetDistance(const Point& a, const Point& b)
{
	const double dx = b.x - a.x;
	const double dy = b.y - a.y;
	return std::sqrt(dx * dx + dy * dy);
}

#endif // POINT_H