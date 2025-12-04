#include "Slide.h"

void Slide::Draw(ICanvas& canvas) const
{
	for (const auto& shape : m_shapes)
	{
		shape->Draw(canvas);
	}
}

size_t Slide::GetShapeCount() const
{
	return m_shapes.size();
}

std::shared_ptr<IShape> Slide::GetShapeAt(size_t index) const
{
	if (index >= m_shapes.size())
	{
		throw std::out_of_range("Shape index out of range in slide");
	}
	return m_shapes[index];
}

void Slide::AddShape(std::shared_ptr<IShape> shape)
{
	if (!shape)
	{
		throw std::invalid_argument("Cannot add nullptr shape to slide");
	}
	m_shapes.push_back(std::move(shape));
}