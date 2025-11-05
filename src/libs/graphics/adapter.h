#pragma once
#include "graphics_lib.h"
#include "modern_graphics_lib.h"

namespace modern_graphics_lib
{
class ModernGraphicsRenderer;
}

class RendererToPainterAdapter final : public graphics_lib::ICanvas
{
public:
	explicit RendererToPainterAdapter(modern_graphics_lib::ModernGraphicsRenderer& renderer)
		: m_renderer(renderer)
		, m_currentX(0)
		, m_currentY(0)
	{
		m_renderer.BeginDraw();
	}

	~RendererToPainterAdapter() override
	{
		m_renderer.EndDraw();
	}

	void MoveTo(int x, int y) override
	{
		m_currentX = x;
		m_currentY = y;
	}

	void LineTo(int x, int y) override
	{
		m_renderer.DrawLine(
			modern_graphics_lib::Point(m_currentX, m_currentY),
			modern_graphics_lib::Point(x, y)
		);

		m_currentX = x;
		m_currentY = y;
	}

private:
	modern_graphics_lib::ModernGraphicsRenderer& m_renderer;
	int m_currentX;
	int m_currentY;
};
