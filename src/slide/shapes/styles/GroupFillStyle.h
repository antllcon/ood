#pragma once
#include "shapes/interfaces/IFillStyle.h"
#include <functional>
#include <memory>

class GroupShape;
class GroupFillStyle : public IFillStyle
{
public:
	GroupFillStyle(const std::shared_ptr<GroupShape>& group);

	std::optional<bool> IsEnabled() const override;
	std::optional<RgbaColor> GetColor() const override;

	void Enable(std::optional<bool> val) override;
	void SetColor(std::optional<RgbaColor> val) override;

private:
	template <typename T>
	std::optional<T> GetHomogeneous(std::function<std::optional<T>(const std::shared_ptr<IFillStyle>&)> getter) const;

private:
	std::weak_ptr<GroupShape> m_group;
};
