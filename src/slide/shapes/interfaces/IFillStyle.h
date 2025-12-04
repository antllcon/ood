#pragma once
#include "common/Color.h"
#include <optional>

class IFillStyle
{
public:
	virtual ~IFillStyle() = default;
	virtual std::optional<bool> IsEnabled() const = 0;
	virtual std::optional<RgbaColor> GetColor() const = 0;

	virtual void Enable(std::optional<bool> enable) = 0;
	virtual void SetColor(std::optional<RgbaColor> color) = 0;
};
