#pragma once
#include "graphics/graphics_lib.h"
#include "graphics/modern_graphics_lib.h"

namespace
{
constexpr int RED_SHIFT = 16;
constexpr int GREEN_SHIFT = 8;
constexpr uint32_t CHANNEL_MASK = 0xFF;
constexpr float NORMALIZE_FACTOR = 255.0f;
} // namespace

class ClassRendererToPainterAdapter final
	: public graphics_lib::ICanvas
	, private modern_graphics_lib::ModernGraphicsRenderer
{
public:
	explicit ClassRendererToPainterAdapter(std::ostream& output)
		: modern_graphics_lib::ModernGraphicsRenderer(output)
		, m_currentX(0)
		, m_currentY(0)
		, m_currentColor(0.0f, 0.0f, 0.0f, 1.0f)
	{
		BeginDraw();
	}

	void SetColor(uint32_t rgbColor) override
	{
		m_currentColor.r = ((rgbColor >> RED_SHIFT) & CHANNEL_MASK) / NORMALIZE_FACTOR;
		m_currentColor.g = ((rgbColor >> GREEN_SHIFT) & CHANNEL_MASK) / NORMALIZE_FACTOR;
		m_currentColor.b = (rgbColor & CHANNEL_MASK) / NORMALIZE_FACTOR;
		m_currentColor.a = 1.0f;
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
			modern_graphics_lib::Point(x, y),
			m_currentColor);
		m_currentX = x;
		m_currentY = y;
	}

private:
	int m_currentX;
	int m_currentY;
	modern_graphics_lib::RGBAColor m_currentColor;
};
