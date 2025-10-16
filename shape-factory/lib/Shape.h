#pragma once
#include "Canvas.h"
#include "Common.h"

class Shape
{
public:
	explicit Shape(Color color)
		: m_color(color)
	{
	}

	virtual ~Shape() = default;
	virtual void Draw(ICanvas& canvas) const = 0;

	Color GetColor() const
	{
		return m_color;
	}

protected:
	Color m_color;
};

class Rectangle final : public Shape
{
public:
	Rectangle(Color color, Point leftTop, Point rightBottom)
		: Shape(color)
		, m_leftTop(leftTop)
		, m_rightBottom(rightBottom)
	{
	}

	void Draw(ICanvas& canvas) const override
	{
		canvas.SetColor(m_color);

		const Point rightTop = {m_rightBottom.x, m_leftTop.y};
		const Point leftBottom = {m_leftTop.x, m_rightBottom.y};

		canvas.DrawLine(m_leftTop, rightTop);
		canvas.DrawLine(rightTop, m_rightBottom);
		canvas.DrawLine(m_rightBottom, leftBottom);
		canvas.DrawLine(leftBottom, m_leftTop);
	}

	Point GetLeftTop() const
	{
		return m_leftTop;
	}

	Point GetRightBottom() const
	{
		return m_rightBottom;
	}

private:
	Point m_leftTop;
	Point m_rightBottom;
};

class Triangle final : public Shape
{
public:
	Triangle(Color color, Point vertex1, Point vertex2, Point vertex3)
		: Shape(color)
		, m_vertex1(vertex1)
		, m_vertex2(vertex2)
		, m_vertex3(vertex3)
	{
	}

	void Draw(ICanvas& canvas) const override
	{
		canvas.SetColor(m_color);
		canvas.DrawLine(m_vertex1, m_vertex2);
		canvas.DrawLine(m_vertex2, m_vertex3);
		canvas.DrawLine(m_vertex3, m_vertex1);
	}

	Point GetVertex1() const
	{
		return m_vertex1;
	}

	Point GetVertex2() const
	{
		return m_vertex2;
	}

	Point GetVertex3() const
	{
		return m_vertex3;
	}

private:
	Point m_vertex1;
	Point m_vertex2;
	Point m_vertex3;
};

class Ellipse final : public Shape
{
public:
	Ellipse(Color color, Point center, int horizontalRadius, int verticalRadius)
		: Shape(color)
		, m_center(center)
		, m_horizontalRadius(horizontalRadius)
		, m_verticalRadius(verticalRadius)
	{
	}

	void Draw(ICanvas& canvas) const override
	{
		canvas.SetColor(m_color);
		canvas.DrawEllipse(m_center, m_horizontalRadius, m_verticalRadius);
	}

	Point GetCenter() const
	{
		return m_center;
	}

	int GetHorizontalRadius() const
	{
		return m_horizontalRadius;
	}

	int GetVerticalRadius() const
	{
		return m_verticalRadius;
	}

private:
	Point m_center;
	int m_horizontalRadius;
	int m_verticalRadius;
};
