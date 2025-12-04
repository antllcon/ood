#include "Frame.h"
#include <algorithm>
#include <cmath>

Frame::Frame(const Point& leftTop, const Point& rightBottom) noexcept
	: LeftTop(leftTop)
	, RightBottom(rightBottom)
{
}

Frame::Frame(const Point& leftTop, double size) noexcept
	: LeftTop(leftTop)
	, RightBottom({leftTop.x + size, leftTop.y + size})
{
}

Frame::Frame(double x1, double y1, double x2, double y2) noexcept
	: LeftTop{x1, y1}
, RightBottom{x2, y2}
{
}

double Frame::GetWidth() const
{
	return RightBottom.x - LeftTop.x;
}

double Frame::GetHeight() const
{
	return RightBottom.y - LeftTop.y;
}

bool Frame::IsEmpty() const
{
	return GetWidth() <= 0.0 || GetHeight() <= 0.0;
}

Frame Frame::GetZeroFrame()
{
	return Frame(0.0, 0.0, 0.0, 0.0);
}

void Frame::Extend(const Frame& other)
{
	if (IsEmpty())
	{
		*this = other;
		return;
	}

	LeftTop.x = std::min(LeftTop.x, other.LeftTop.x);
	LeftTop.y = std::min(LeftTop.y, other.LeftTop.y);
	RightBottom.x = std::max(RightBottom.x, other.RightBottom.x);
	RightBottom.y = std::max(RightBottom.y, other.RightBottom.y);
}