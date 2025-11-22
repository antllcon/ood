#pragma once

#include "Common.h"
#include "Shape.h"

class Triangle : public Shape
{
public:
	Triangle(Point p1, Point p2, Point p3)
		: m_p1(p1)
		, m_p2(p2)
		, m_p3(p3)
	{
	}

	Frame GetFrame() const override
	{
		double minX = std::min({m_p1.X, m_p2.X, m_p3.X});
		double minY = std::min({m_p1.Y, m_p2.Y, m_p3.Y});
		double maxX = std::max({m_p1.X, m_p2.X, m_p3.X});
		double maxY = std::max({m_p1.Y, m_p2.Y, m_p3.Y});

		return Frame(minX, minY, maxX, maxY);
	}

	void SetFrame(double x1, double y1, double x2, double y2) override
	{
		Frame oldFrame = GetFrame();
		double oldW = oldFrame.RightBottom.X - oldFrame.LeftTop.X;
		double oldH = oldFrame.RightBottom.Y - oldFrame.LeftTop.Y;

		if (oldW == 0 || oldH == 0) return;

		double scaleX = (x2 - x1) / oldW;
		double scaleY = (y2 - y1) / oldH;

		auto transform = [&](Point& p) {
			p.X = x1 + (p.X - oldFrame.LeftTop.X) * scaleX;
			p.Y = y1 + (p.Y - oldFrame.LeftTop.Y) * scaleY;
		};

		transform(m_p1);
		transform(m_p2);
		transform(m_p3);
	}

protected:
	void DoDraw(ICanvas& canvas) const override
	{
		if (m_fillStyle.has_value() && m_fillStyle->IsEnabled)
		{
			canvas.FillPolygon({m_p1, m_p2, m_p3});
		}
		if (m_lineStyle.has_value() && m_lineStyle->IsEnabled)
		{
			canvas.DrawLine(m_p1, m_p2);
			canvas.DrawLine(m_p2, m_p3);
			canvas.DrawLine(m_p3, m_p1);
		}
	}

private:
	Point m_p1;
	Point m_p2;
	Point m_p3;
};