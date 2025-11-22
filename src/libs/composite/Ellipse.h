#pragma once
#include "Shape.h"
#include "Common.h"

class Ellipse : public Shape
{
public:
	Ellipse(Point center, double rx, double ry)
		: m_center(center)
		, m_rx(rx)
		, m_ry(ry)
	{
	}

	Frame GetFrame() const override
	{
		return Frame(
			m_center.X - m_rx, m_center.Y - m_ry,
			m_center.X + m_rx, m_center.Y + m_ry
		);
	}

	void SetFrame(double x1, double y1, double x2, double y2) override
	{
		m_rx = (x2 - x1) / 2.0;
		m_ry = (y2 - y1) / 2.0;
		m_center.X = x1 + m_rx;
		m_center.Y = y1 + m_ry;
	}

protected:
	void DoDraw(ICanvas& canvas) const override
	{
		if (m_fillStyle.has_value() && m_fillStyle->IsEnabled)
		{
			canvas.FillEllipse(m_center, m_rx, m_ry);
		}
		if (m_lineStyle.has_value() && m_lineStyle->IsEnabled)
		{
			canvas.DrawEllipse(m_center, m_rx, m_ry);
		}
	}

private:
	Point m_center;
	double m_rx;
	double m_ry;
};