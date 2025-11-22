#pragma once
#include "Shape.h"

class ShapeGroup : public Shape, public IShapes
{
public:
	ShapeGroup() = default;

	// IShapes implementation
	size_t GetShapesCount() const override
	{
		return m_shapes.size();
	}

	void InsertShape(std::shared_ptr<IShape> shape, size_t position) override
	{
		if (!shape) return;

		shape->SetParent(this);

		if (position >= m_shapes.size())
		{
			m_shapes.push_back(shape);
		}
		else
		{
			m_shapes.insert(m_shapes.begin() + position, shape);
		}

		UpdateCompositeStyles();
	}

	std::shared_ptr<IShape> GetShapeAt(size_t position) override
	{
		if (position >= m_shapes.size())
		{
			throw std::out_of_range("Index out of range");
		}
		return m_shapes[position];
	}

	void RemoveShapeAt(size_t position) override
	{
		if (position >= m_shapes.size())
		{
			throw std::out_of_range("Index out of range");
		}
		m_shapes.erase(m_shapes.begin() + position);
		UpdateCompositeStyles();
	}

	// IShape implementation
	std::shared_ptr<IShapes> GetShapesGroup() override
	{
		// shared_from_this() требует, чтобы объект уже управлялся shared_ptr
		return std::dynamic_pointer_cast<IShapes>(shared_from_this());
	}

	Frame GetFrame() const override
	{
		if (m_shapes.empty())
		{
			return Frame(0, 0, 0, 0);
		}

		double minX = std::numeric_limits<double>::max();
		double minY = std::numeric_limits<double>::max();
		double maxX = std::numeric_limits<double>::lowest();
		double maxY = std::numeric_limits<double>::lowest();

		for (const auto& shape : m_shapes)
		{
			Frame frame = shape->GetFrame();
			minX = std::min(minX, frame.LeftTop.X);
			minY = std::min(minY, frame.LeftTop.Y);
			maxX = std::max(maxX, frame.RightBottom.X);
			maxY = std::max(maxY, frame.RightBottom.Y);
		}

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

		for (auto& shape : m_shapes)
		{
			Frame sFrame = shape->GetFrame();
			double sOffsetX = sFrame.LeftTop.X - oldFrame.LeftTop.X;
			double sOffsetY = sFrame.LeftTop.Y - oldFrame.LeftTop.Y;
			double sW = sFrame.RightBottom.X - sFrame.LeftTop.X;
			double sH = sFrame.RightBottom.Y - sFrame.LeftTop.Y;

			double newX1 = x1 + sOffsetX * scaleX;
			double newY1 = y1 + sOffsetY * scaleY;

			shape->SetFrame(newX1, newY1, newX1 + sW * scaleX, newY1 + sH * scaleY);
		}
	}

protected:
	void DoDraw(ICanvas& canvas) const override
	{
		for (const auto& shape : m_shapes)
		{
			shape->Draw(canvas);
		}
	}

	void DoSetLineStyleToChildren(bool isEnabled, RgbaColor color, double width) override
	{
		for (auto& shape : m_shapes)
		{
			shape->SetLineStyle(isEnabled, color, width);
		}
	}

	void DoSetFillStyleToChildren(bool isEnabled, RgbaColor color) override
	{
		for (auto& shape : m_shapes)
		{
			shape->SetFillStyle(isEnabled, color);
		}
	}

private:
	void UpdateCompositeStyles()
	{
		if (m_shapes.empty()) return;

		// Update Fill Style
		auto firstFill = m_shapes[0]->GetFillStyle();
		bool allFillEqual = true;
		for (size_t i = 1; i < m_shapes.size(); ++i)
		{
			if (m_shapes[i]->GetFillStyle() != firstFill)
			{
				allFillEqual = false;
				break;
			}
		}
		m_fillStyle = allFillEqual ? firstFill : std::nullopt;

		// Update Line Style
		auto firstLine = m_shapes[0]->GetLineStyle();
		bool allLineEqual = true;
		for (size_t i = 1; i < m_shapes.size(); ++i)
		{
			if (m_shapes[i]->GetLineStyle() != firstLine)
			{
				allLineEqual = false;
				break;
			}
		}
		m_lineStyle = allLineEqual ? firstLine : std::nullopt;
	}

	std::vector<std::shared_ptr<IShape>> m_shapes;
};