#pragma once
#include <functional>
#include <memory>
#include "shapes/interfaces/ILineStyle.h"

class GroupShape;

class GroupLineStyle : public ILineStyle
{
public:
	GroupLineStyle(const std::shared_ptr<GroupShape>& group);

	std::optional<bool> IsEnabled() const override;
	std::optional<RgbaColor> GetColor() const override;
	std::optional<double> GetThickness() const override;

	void Enable(std::optional<bool> val) override;
	void SetColor(std::optional<RgbaColor> val) override;
	void SetThickness(std::optional<double> val) override;

private:
	template <typename T>
	std::optional<T> GetHomogeneous(std::function<std::optional<T>(const std::shared_ptr<ILineStyle>&)> getter) const;

private:
	std::weak_ptr<GroupShape> m_group;
};
