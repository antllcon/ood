#pragma once
#include "shapes/interfaces/ILineStyle.h"

class SimpleLineStyle : public ILineStyle
{
	RgbaColor m_color;
	double m_thickness;
	bool m_enabled;

public:
	SimpleLineStyle(const RgbaColor& color = {0, 0, 0, 1}, double thickness = 1.0, bool enabled = true)
		: m_color(color)
		, m_thickness(thickness)
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

	std::optional<double> GetThickness() const override
	{
		return m_thickness;
	}

	void Enable(std::optional<bool> enable) override
	{
		if (enable) m_enabled = *enable;
	}

	void SetColor(std::optional<RgbaColor> color) override
	{
		if (color) m_color = *color;
	}

	void SetThickness(std::optional<double> thickness) override
	{
		if (thickness) m_thickness = *thickness;
	}
};
