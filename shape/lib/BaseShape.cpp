#include "BaseShape.h"

namespace
{
void AssertIsIDExist(const std::string& id)
{
	if (id.empty())
	{
		throw std::invalid_argument("ID cannot be empty");
	}
}
} // namespace

BaseShape::BaseShape(const std::string& id, Color color)
	: m_id(id)
	, m_color(color)
{
	AssertIsIDExist(id);
}

std::string BaseShape::GetId() const
{
	return m_id;
}

Color BaseShape::GetColor() const
{
	return m_color;
}

void BaseShape::SetColor(const Color color)
{
	m_color = color;
}

void BaseShape::AssertIsValidParams(const std::vector<std::string>& params, const size_t count)
{
	if (params.size() != count)
	{
		throw std::invalid_argument("Invalid number of parameters");
	}

	for (const std::string& param : params)
	{
		if (param.empty())
		{
			throw std::invalid_argument("Invalid parameter");
		}
	}
}

void BaseShape::ChangeParameters(IShape* source)
{
	if (GetType() != source->GetType())
	{
		throw std::invalid_argument("Cannot change parameters from different shape type");
	}
}
