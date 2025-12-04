#include "Ellipse.h"
#include <stdexcept>

Ellipse::Ellipse(const Frame& frame)
	: m_frame(frame)
	, m_line(std::make_shared<SimpleLineStyle>())
	, m_fill(std::make_shared<SimpleFillStyle>())
{
}

void Ellipse::Draw(ICanvas& canvas) const
{
	double rx = m_frame.GetWidth() / 2;
	double ry = m_frame.GetHeight() / 2;

	Point center = {m_frame.LeftTop.x + rx, m_frame.LeftTop.y + ry};

	if (m_fill->IsEnabled().value_or(false))
	{
		canvas.SetFillColor(*m_fill->GetColor());
		canvas.FillEllipse(center, rx, ry);
	}

	if (m_line->IsEnabled().value_or(false))
	{
		canvas.SetStrokeColor(*m_line->GetColor());
		canvas.SetStrokeWidth(*m_line->GetThickness());
		canvas.DrawEllipse(center, rx, ry);
	}
}

Frame Ellipse::GetFrame() const
{
	return m_frame;
}

void Ellipse::SetFrame(const Frame& frame)
{
	m_frame = frame;
}

std::shared_ptr<ILineStyle> Ellipse::GetLineStyle() const
{
	return m_line;
}

std::shared_ptr<IFillStyle> Ellipse::GetFillStyle() const
{
	return m_fill;
}

size_t Ellipse::GetShapeCount() const
{
	return 0;
}

std::shared_ptr<IShape> Ellipse::GetShapeAt(size_t) const
{
	throw std::out_of_range("Leaf");
}

void Ellipse::AddShape(std::shared_ptr<IShape>)
{
	throw std::runtime_error("Leaf");
}

void Ellipse::RemoveShapeAt(size_t)
{
	throw std::out_of_range("Leaf");
}

std::unique_ptr<IShape> Ellipse::Clone() const
{
	auto clone = std::make_unique<Ellipse>(m_frame);
	*clone->m_line = *m_line;
	*clone->m_fill = *m_fill;
	return clone;
}