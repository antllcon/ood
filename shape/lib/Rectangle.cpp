#include "Rectangle.h"
#include <stdexcept>

namespace
{
constexpr size_t COUNT_PARAMETERS = 4;
}

Rectangle::Rectangle(const std::string& id, const Color color, const std::vector<std::string>& params)
	: BaseShape(id, color)
{
	AssertIsValidParams(params, COUNT_PARAMETERS);
	m_topLeft.x = std::stod(params[1]);
	m_topLeft.y = std::stod(params[2]);
	m_width = std::stod(params[3]);
	m_height = std::stod(params[4]);
}

void Rectangle::Draw(ICanvas* canvas)
{
	// TODO: реализовать
}

void Rectangle::Move(double dx, double dy)
{
	// TODO: реализовать
}

std::string Rectangle::GetType() const
{
	return "rectangle";
}

void Rectangle::ChangeParameters(IShape* source)
{
	// TODO: реализовать
}