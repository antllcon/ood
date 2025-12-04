#include "GroupFillStyle.h"
#include "shapes/entities/GroupShape.h"

GroupFillStyle::GroupFillStyle(const std::shared_ptr<GroupShape>& groupShape)
	: m_group(groupShape)
{
}

template <typename T>
std::optional<T> GroupFillStyle::GetHomogeneous(
	std::function<std::optional<T>(const std::shared_ptr<IFillStyle>&)> stylePropertyGetter) const
{
	auto group = m_group.lock();

	if (!group || group->GetShapeCount() == 0)
	{
		return std::nullopt;
	}

	auto firstStyle = group->GetShapeAt(0)->GetFillStyle();
	auto commonValue = stylePropertyGetter(firstStyle);

	if (!commonValue)
	{
		return std::nullopt;
	}

	for (size_t shapeIndex = 1; shapeIndex < group->GetShapeCount(); ++shapeIndex)
	{
		auto nextStyle = group->GetShapeAt(shapeIndex)->GetFillStyle();
		if (stylePropertyGetter(nextStyle) != commonValue)
		{
			return std::nullopt;
		}
	}

	return commonValue;
}

std::optional<bool> GroupFillStyle::IsEnabled() const
{
	return GetHomogeneous<bool>([](const std::shared_ptr<IFillStyle>& style) {
		return style->IsEnabled();
	});
}

std::optional<RgbaColor> GroupFillStyle::GetColor() const
{
	return GetHomogeneous<RgbaColor>([](const std::shared_ptr<IFillStyle>& style) {
		return style->GetColor();
	});
}

void GroupFillStyle::Enable(std::optional<bool> enable)
{
	if (!enable.has_value())
	{
		return;
	}

	auto group = m_group.lock();
	if (!group) return;

	for (size_t shapeIndex = 0; shapeIndex < group->GetShapeCount(); ++shapeIndex)
	{
		group->GetShapeAt(shapeIndex)->GetFillStyle()->Enable(enable);
	}
}

void GroupFillStyle::SetColor(std::optional<RgbaColor> color)
{
	if (!color.has_value())
	{
		return;
	}

	auto group = m_group.lock();
	if (!group) return;

	for (size_t shapeIndex = 0; shapeIndex < group->GetShapeCount(); ++shapeIndex)
	{
		group->GetShapeAt(shapeIndex)->GetFillStyle()->SetColor(color);
	}
}