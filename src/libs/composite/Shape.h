#pragma once
#include "IShape.h"

class Shape : public IShape, public std::enable_shared_from_this<Shape>
{
public:
	void Draw(ICanvas& canvas) override
	{
		if (m_lineStyle.has_value())
		{
			canvas.SetStrokeColor(m_lineStyle->Color);
			canvas.SetStrokeWidth(m_lineStyle->Width);
		}
		else
		{
			canvas.SetStrokeColor({ 0, 0, 0, 0 });
			canvas.SetStrokeWidth(0);
		}

		if (m_fillStyle.has_value())
		{
			canvas.SetFillColor(m_fillStyle->Color);
		}
		else
		{
			canvas.SetFillColor({ 0, 0, 0, 0 });
		}

		DoDraw(canvas);
	}

	std::optional<LineStyle> GetLineStyle() const override
	{
		return m_lineStyle;
	}

	std::optional<FillStyle> GetFillStyle() const override
	{
		return m_fillStyle;
	}

	void SetLineStyle(bool isEnabled, RgbaColor color, double width) override
	{
		m_lineStyle = LineStyle{ color, width, isEnabled };
		DoSetLineStyleToChildren(isEnabled, color, width);
		// Уведомление родителя об изменении (упрощено для примера)
	}

	void SetFillStyle(bool isEnabled, RgbaColor color) override
	{
		m_fillStyle = FillStyle{ color, isEnabled };
		DoSetFillStyleToChildren(isEnabled, color);
	}

	std::shared_ptr<IShapes> GetShapesGroup() override
	{
		return nullptr;
	}

	void SetParent(IShapes* parent) override
	{
		m_parent = parent;
	}

protected:
	virtual void DoDraw(ICanvas& canvas) const = 0;
	virtual void DoSetLineStyleToChildren(bool isEnabled, RgbaColor color, double width) {}
	virtual void DoSetFillStyleToChildren(bool isEnabled, RgbaColor color) {}

	IShapes* m_parent = nullptr;
	std::optional<LineStyle> m_lineStyle;
	std::optional<FillStyle> m_fillStyle;
};