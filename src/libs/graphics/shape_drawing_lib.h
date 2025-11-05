#pragma once
#include "graphics_lib.h"

namespace shape_drawing_lib
{
struct Point
{
	int x;
	int y;
};

// Интерфейс объектов, которые могут быть
// нарисованы на холсте из graphics_lib
class ICanvasDrawable
{
public:
	virtual void Draw(graphics_lib::ICanvas& canvas) const = 0;
	virtual ~ICanvasDrawable() = default;
};

class Triangle final : public ICanvasDrawable
{
public:
	Triangle(const Point& p1, const Point& p2, const Point& p3)
		: m_p1(p1)
		, m_p2(p2)
		, m_p3(p3)
	{
	}

	void Draw(graphics_lib::ICanvas& canvas) const override
	{
		canvas.MoveTo(m_p1.x, m_p1.y);
		canvas.LineTo(m_p2.x, m_p2.y);
		canvas.LineTo(m_p3.x, m_p3.y);
		canvas.LineTo(m_p1.x, m_p1.y);
	}

private:
	Point m_p1, m_p2, m_p3;
};

class Rectangle final : public ICanvasDrawable
{
public:
	Rectangle(const Point& leftTop, int width, int height)
		: m_leftTop(leftTop)
		, m_width(width)
		, m_height(height)
	{
	}

	void Draw(graphics_lib::ICanvas& canvas) const override
	{
		Point rightTop = {m_leftTop.x + m_width, m_leftTop.y};
		Point rightBottom = {m_leftTop.x + m_width, m_leftTop.y + m_height};
		Point leftBottom = {m_leftTop.x, m_leftTop.y + m_height};

		canvas.MoveTo(m_leftTop.x, m_leftTop.y);
		canvas.LineTo(rightTop.x, rightTop.y);
		canvas.LineTo(rightBottom.x, rightBottom.y);
		canvas.LineTo(leftBottom.x, leftBottom.y);
		canvas.LineTo(m_leftTop.x, m_leftTop.y);
	}

private:
	Point m_leftTop;
	int m_width;
	int m_height;
};

class CanvasPainter
{
public:
	explicit CanvasPainter(graphics_lib::ICanvas& canvas)
		: m_canvas(canvas)
	{
	}

	void Draw(const ICanvasDrawable& drawable)
	{
		drawable.Draw(m_canvas);
	}

private:
	graphics_lib::ICanvas& m_canvas;
};
} // namespace shape_drawing_lib