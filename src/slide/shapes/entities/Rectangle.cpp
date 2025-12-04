#include "Rectangle.h"
#include <stdexcept>

Rectangle::Rectangle(const Frame& frame)
	: m_frame(frame)
	, m_line(std::make_shared<SimpleLineStyle>())
	, m_fill(std::make_shared<SimpleFillStyle>())
{
}

void Rectangle::Draw(ICanvas& canvas) const
{
	const auto& topLeft = m_frame.LeftTop;
	const auto& bottomRight = m_frame.RightBottom;
	Point topRight{bottomRight.x, topLeft.y};
	Point bottomLeft{topLeft.x, bottomRight.y};

	if (m_fill->IsEnabled().value_or(false))
	{
		if (auto color = m_fill->GetColor())
		{
			canvas.SetFillColor(*color);
			canvas.FillPolygon({topLeft, topRight, bottomRight, bottomLeft});
		}
	}

	if (m_line->IsEnabled().value_or(false))
	{
		if (auto color = m_line->GetColor())
			if (auto thickness = m_line->GetThickness())
			{
				canvas.SetStrokeColor(*color);
				canvas.SetStrokeWidth(*thickness);

				canvas.DrawLine(topLeft, topRight);
				canvas.DrawLine(topRight, bottomRight);
				canvas.DrawLine(bottomRight, bottomLeft);
				canvas.DrawLine(bottomLeft, topLeft);
			}
	}
}

Frame Rectangle::GetFrame() const
{
	return m_frame;
}

void Rectangle::SetFrame(const Frame& frame)
{
	m_frame = frame;
}

std::shared_ptr<ILineStyle> Rectangle::GetLineStyle() const
{
	return m_line;
}

std::shared_ptr<IFillStyle> Rectangle::GetFillStyle() const
{
	return m_fill;
}

size_t Rectangle::GetShapeCount() const
{
	return 0;
}

std::shared_ptr<IShape> Rectangle::GetShapeAt(size_t) const
{
	throw std::out_of_range("Leaf");
}

void Rectangle::AddShape(std::shared_ptr<IShape>)
{
	throw std::runtime_error("Leaf");
}

void Rectangle::RemoveShapeAt(size_t)
{
	throw std::out_of_range("Leaf");
}

std::unique_ptr<IShape> Rectangle::Clone() const
{
	auto clone = std::make_unique<Rectangle>(m_frame);
	*clone->m_line = *m_line;
	*clone->m_fill = *m_fill;
	return clone;
}