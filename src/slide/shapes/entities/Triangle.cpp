#include "Triangle.h"
#include <stdexcept>

Triangle::Triangle(const Frame& frame)
	: m_frame(frame)
	, m_line(std::make_shared<SimpleLineStyle>())
	, m_fill(std::make_shared<SimpleFillStyle>())
{
}

Frame Triangle::GetFrame() const
{
	return m_frame;
}

void Triangle::SetFrame(const Frame& frame)
{
	m_frame = frame;
}

std::shared_ptr<ILineStyle> Triangle::GetLineStyle() const
{
	return m_line;
}

std::shared_ptr<IFillStyle> Triangle::GetFillStyle() const
{
	return m_fill;
}

size_t Triangle::GetShapeCount() const
{
	return 0;
}

std::shared_ptr<IShape> Triangle::GetShapeAt(size_t) const
{
	throw std::out_of_range("Leaf");
}

void Triangle::AddShape(std::shared_ptr<IShape>)
{
	throw std::runtime_error("Leaf");
}

void Triangle::RemoveShapeAt(size_t)
{
	throw std::out_of_range("Leaf");
}

std::unique_ptr<IShape> Triangle::Clone() const
{
	auto clone = std::make_unique<Triangle>(m_frame);
	*clone->m_line = *m_line;
	*clone->m_fill = *m_fill;
	return clone;
}

void Triangle::Draw(ICanvas& canvas) const
{
	const double halfWidth = m_frame.GetWidth() / 2.0;
	const double centerX = m_frame.LeftTop.x + halfWidth;

	const Point topVertex{centerX, m_frame.LeftTop.y};
	const Point leftBottom{m_frame.LeftTop.x, m_frame.RightBottom.y};
	const Point rightBottom{m_frame.RightBottom.x, m_frame.RightBottom.y};

	const std::vector<Point> vertices{topVertex, leftBottom, rightBottom};

	if (auto fillEnabled = m_fill->IsEnabled(); fillEnabled.value_or(false))
	{
		if (auto fillColor = m_fill->GetColor())
		{
			canvas.SetFillColor(*fillColor);
			canvas.FillPolygon(vertices);
		}
	}

	if (auto lineEnabled = m_line->IsEnabled(); lineEnabled.value_or(false))
	{
		if (auto lineColor = m_line->GetColor())
			if (auto lineThickness = m_line->GetThickness())
			{
				canvas.SetStrokeColor(*lineColor);
				canvas.SetStrokeWidth(*lineThickness);

				canvas.DrawLine(topVertex, leftBottom);
				canvas.DrawLine(leftBottom, rightBottom);
				canvas.DrawLine(rightBottom, topVertex);
			}
	}
}