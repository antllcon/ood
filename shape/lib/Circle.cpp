#include "Circle.h"

namespace
{
constexpr size_t COUNT_PARAMETERS = 3;
} // namespace

Circle::Circle(const std::string& id, const Color color, const std::vector<std::string>& params)
	: BaseShape(id, color)
{
	AssertIsValidParams(params, COUNT_PARAMETERS);
	m_center.x = std::stod(params[0]);
	m_center.y = std::stod(params[1]);
	m_radius = std::stod(params[2]);
}

void Circle::Draw(ICanvas* canvas)
{
	if (!canvas)
	{
		throw std::invalid_argument("Canvas cannot be null");
	}

	canvas->SetColor(GetColor());
	canvas->DrawEllipse(m_center, m_radius, m_radius);
}

void Circle::Move(const double dx, const double dy)
{
	m_center.x += dx;
	m_center.y += dy;
}

std::string Circle::GetType() const
{
	return "Circle";
}

// TODO: сделать без каста, а то котёнок умирает :(
void Circle::ChangeParameters(IShape* source)
{
	if (const auto circle = dynamic_cast<Circle*>(source))
	{
		m_center = circle->m_center;
		m_radius = circle->m_radius;
	}
	else
	{
		throw std::invalid_argument("Cannot change parameters from different shape type");
	}
}