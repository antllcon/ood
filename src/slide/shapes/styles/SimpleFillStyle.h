#pragma once
#include "shapes/interfaces/IFillStyle.h"

class SimpleFillStyle : public IFillStyle
{
	RgbaColor m_color;
	bool m_enabled;

public:
	SimpleFillStyle(const RgbaColor& color = {1, 1, 1, 1}, bool enabled = true)
		: m_color(color)
		, m_enabled(enabled)
	{
	}

	std::optional<bool> IsEnabled() const override
	{
		return m_enabled;
	}

	std::optional<RgbaColor> GetColor() const override
	{
		return m_color;
	}

	void Enable(std::optional<bool> enable) override
	{
		if (enable) m_enabled = *enable;
	}

	void SetColor(std::optional<RgbaColor> color) override
	{
		if (color) m_color = *color;
	}
};