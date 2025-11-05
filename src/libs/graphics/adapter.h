#pragma once
#include "graphics/graphics_lib.h"
#include "graphics/modern_graphics_lib.h"

class ClassRendererToPainterAdapter final : public graphics_lib::ICanvas
	, private modern_graphics_lib::ModernGraphicsRenderer
{
public:
	explicit ClassRendererToPainterAdapter(std::ostream& output)
		: modern_graphics_lib::ModernGraphicsRenderer(output)
		, m_currentX(0)
		, m_currentY(0)
	{
		BeginDraw();
	}

	~ClassRendererToPainterAdapter() override
	{
		EndDraw();
	}

	void MoveTo(int x, int y) override
	{
		m_currentX = x;
		m_currentY = y;
	}

	void LineTo(int x, int y) override
	{
		DrawLine(
			modern_graphics_lib::Point(m_currentX, m_currentY),
			modern_graphics_lib::Point(x, y));
		m_currentX = x;
		m_currentY = y;
	}

private:
	int m_currentX;
	int m_currentY;
};
