
#pragma once
#include "Common.h"
#include "Shape.h"

class Rectangle : public Shape
{
public:
	Rectangle(double x1, double y1, double x2, double y2)
		: m_leftTop{x1, y1}
		, m_rightBottom{x2, y2}
	{
	}

	Frame GetFrame() const override
	{
		return Frame(m_leftTop.X, m_leftTop.Y, m_rightBottom.X, m_rightBottom.Y);
	}

	void SetFrame(double x1, double y1, double x2, double y2) override
	{
		m_leftTop = {x1, y1};
		m_rightBottom = {x2, y2};
	}

protected:
	void DoDraw(ICanvas& canvas) const override
	{
		Point rt{m_rightBottom.X, m_leftTop.Y};
		Point lb{m_leftTop.X, m_rightBottom.Y};

		if (m_fillStyle.has_value() && m_fillStyle->IsEnabled)
		{
			canvas.FillPolygon({m_leftTop, rt, m_rightBottom, lb});
		}
		if (m_lineStyle.has_value() && m_lineStyle->IsEnabled)
		{
			canvas.DrawLine(m_leftTop, rt);
			canvas.DrawLine(rt, m_rightBottom);
			canvas.DrawLine(m_rightBottom, lb);
			canvas.DrawLine(lb, m_leftTop);
		}
	}

private:
	Point m_leftTop;
	Point m_rightBottom;
};