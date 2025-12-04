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

// TODO: написать чуть лучше (красиво)
void Triangle::Draw(ICanvas& canvas) const
{
	double w = m_frame.GetWidth();

	Point p1 = {m_frame.LeftTop.x + w / 2, m_frame.LeftTop.y};
	Point p2 = {m_frame.LeftTop.x, m_frame.RightBottom.y};
	Point p3 = {m_frame.RightBottom.x, m_frame.RightBottom.y};

	if (m_fill->IsEnabled().value_or(false))
	{
		canvas.SetFillColor(*m_fill->GetColor());
		canvas.FillPolygon({p1, p2, p3});
	}

	if (m_line->IsEnabled().value_or(false))
	{
		canvas.SetStrokeColor(*m_line->GetColor());
		canvas.SetStrokeWidth(*m_line->GetThickness());

		canvas.DrawLine(p1, p2);
		canvas.DrawLine(p2, p3);
		canvas.DrawLine(p3, p1);
	}
}