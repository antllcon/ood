#include "GroupLineStyle.h"
#include "shapes/entities/GroupShape.h"

GroupLineStyle::GroupLineStyle(const std::shared_ptr<GroupShape>& groupShape)
	: m_group(groupShape)
{
}

template <typename T>
std::optional<T> GroupLineStyle::GetHomogeneous(
	std::function<std::optional<T>(const std::shared_ptr<ILineStyle>&)> stylePropertyGetter) const
{
	auto group = m_group.lock();

	if (!group || group->GetShapeCount() == 0)
	{
		return std::nullopt;
	}

	auto firstStyle = group->GetShapeAt(0)->GetLineStyle();
	auto commonValue = stylePropertyGetter(firstStyle);

	if (!commonValue)
	{
		return std::nullopt;
	}

	for (size_t shapeIndex = 1; shapeIndex < group->GetShapeCount(); ++shapeIndex)
	{
		auto nextStyle = group->GetShapeAt(shapeIndex)->GetLineStyle();
		if (stylePropertyGetter(nextStyle) != commonValue)
		{
			return std::nullopt;
		}
	}

	return commonValue;
}

std::optional<bool> GroupLineStyle::IsEnabled() const
{
	return GetHomogeneous<bool>([](const auto& style) { return style->IsEnabled(); });
}

std::optional<RgbaColor> GroupLineStyle::GetColor() const
{
	return GetHomogeneous<RgbaColor>([](const auto& style) { return style->GetColor(); });
}

std::optional<double> GroupLineStyle::GetThickness() const
{
	return GetHomogeneous<double>([](const auto& style) { return style->GetThickness(); });
}

void GroupLineStyle::Enable(std::optional<bool> enable)
{
	if (!enable.has_value()) return;

	auto group = m_group.lock();
	if (!group) return;

	for (size_t shapeIndex = 0; shapeIndex < group->GetShapeCount(); ++shapeIndex)
	{
		group->GetShapeAt(shapeIndex)->GetLineStyle()->Enable(enable);
	}
}

void GroupLineStyle::SetColor(std::optional<RgbaColor> color)
{
	if (!color.has_value()) return;

	auto group = m_group.lock();
	if (!group) return;

	for (size_t shapeIndex = 0; shapeIndex < group->GetShapeCount(); ++shapeIndex)
	{
		group->GetShapeAt(shapeIndex)->GetLineStyle()->SetColor(color);
	}
}

void GroupLineStyle::SetThickness(std::optional<double> thickness)
{
	if (!thickness.has_value()) return;

	auto group = m_group.lock();
	if (!group) return;

	for (size_t shapeIndex = 0; shapeIndex < group->GetShapeCount(); ++shapeIndex)
	{
		group->GetShapeAt(shapeIndex)->GetLineStyle()->SetThickness(thickness);
	}
}