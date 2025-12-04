#pragma once
#include "common/Color.h"
#include <optional>

class ILineStyle
{
public:
	virtual ~ILineStyle() = default;
	virtual std::optional<bool> IsEnabled() const = 0;
	virtual std::optional<RgbaColor> GetColor() const = 0;
	virtual std::optional<double> GetThickness() const = 0;

	virtual void Enable(std::optional<bool> enable) = 0;
	virtual void SetColor(std::optional<RgbaColor> color) = 0;
	virtual void SetThickness(std::optional<double> thickness) = 0;
};