#include "GroupShape.h"
#include "shapes/styles/GroupFillStyle.h"
#include "shapes/styles/GroupLineStyle.h"
#include <algorithm>
#include <stdexcept>

GroupShape::GroupShape()
	: m_line(std::make_shared<GroupLineStyle>(std::shared_ptr<GroupShape>(nullptr)))
	, m_fill(std::make_shared<GroupFillStyle>(std::shared_ptr<GroupShape>(nullptr)))
{
}

void GroupShape::Draw(ICanvas& canvas) const
{
	for (const auto& shape : m_shapes)
	{
		shape->Draw(canvas);
	}
}

Frame GroupShape::GetFrame() const
{
	if (m_shapes.empty())
	{
		return Frame(0, 0, 0, 0);
	}

	auto firstFrame = m_shapes.front()->GetFrame();

	double minX = firstFrame.LeftTop.x;
	double minY = firstFrame.LeftTop.y;
	double maxX = firstFrame.RightBottom.x;
	double maxY = firstFrame.RightBottom.y;

	for (size_t i = 1; i < m_shapes.size(); ++i)
	{
		auto frame = m_shapes[i]->GetFrame();

		minX = std::min(minX, frame.LeftTop.x);
		minY = std::min(minY, frame.LeftTop.y);

		maxX = std::max(maxX, frame.RightBottom.x);
		maxY = std::max(maxY, frame.RightBottom.y);
	}

	return Frame(minX, minY, maxX, maxY);
}

void GroupShape::SetFrame(const Frame& newFrame)
{
	if (m_shapes.empty())
	{
		return;
	}

	auto oldFrame = GetFrame();
	double oldWidth = oldFrame.GetWidth();
	double oldHeight = oldFrame.GetHeight();

	if (oldWidth == 0 || oldHeight == 0)
	{
		return;
	}

	double newWidth = newFrame.GetWidth();
	double newHeight = newFrame.GetHeight();

	double scaleX = newWidth / oldWidth;
	double scaleY = newHeight / oldHeight;

	for (auto& shape : m_shapes)
	{
		auto shapeFrame = shape->GetFrame();

		double offsetX = shapeFrame.LeftTop.x - oldFrame.LeftTop.x;
		double offsetY = shapeFrame.LeftTop.y - oldFrame.LeftTop.y;

		double newShapeX = newFrame.LeftTop.x + offsetX * scaleX;
		double newShapeY = newFrame.LeftTop.y + offsetY * scaleY;

		double newShapeWidth = shapeFrame.GetWidth() * scaleX;
		double newShapeHeight = shapeFrame.GetHeight() * scaleY;

		shape->SetFrame(Frame(
			newShapeX,
			newShapeY,
			newShapeX + newShapeWidth,
			newShapeY + newShapeHeight));
	}
}

std::shared_ptr<ILineStyle> GroupShape::GetLineStyle() const
{
	return m_line;
}

std::shared_ptr<IFillStyle> GroupShape::GetFillStyle() const
{
	return m_fill;
}

size_t GroupShape::GetShapeCount() const
{
	return m_shapes.size();
}

std::shared_ptr<IShape> GroupShape::GetShapeAt(size_t index) const
{
	if (index >= m_shapes.size())
	{
		throw std::out_of_range("Index out of range");
	}
	return m_shapes.at(index);
}

void GroupShape::AddShape(std::shared_ptr<IShape> shape)
{
	if (shape && shape.get() != this)
	{
		m_shapes.push_back(shape);
	}
}

void GroupShape::RemoveShapeAt(size_t index)
{
	if (index < m_shapes.size())
	{
		m_shapes.erase(m_shapes.begin() + index);
	}
}

std::unique_ptr<IShape> GroupShape::Clone() const
{
	auto clone = std::make_unique<GroupShape>();
	for (size_t i = 0; i < GetShapeCount(); ++i)
	{
		clone->AddShape(GetShapeAt(i)->Clone());
	}
	return clone;
}

std::shared_ptr<GroupShape> GroupShape::GetComposite()
{
	return shared_from_this();
}