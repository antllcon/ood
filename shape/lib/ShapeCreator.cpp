#include "ShapeCreator.h"

#include "Circle.h"
#include "Line.h"
#include "Rectangle.h"
#include "TextShape.h"
#include "Triangle.h"

std::unique_ptr<IShape> ShapeCreator::CreateShape(
	const std::string& id,
	const std::string& colorStr,
	const std::string& type,
	const std::vector<std::string>& params)
{
	Color color = Color::FromString(colorStr);

	if (type == "circle")
	{
		return std::make_unique<Circle>(id, color, params);
	}

	if (type == "rectangle")
	{
		return std::make_unique<Rectangle>(id, color, params);
	}

	if (type == "triangle")
	{
		return std::make_unique<Triangle>(id, color, params);
	}

	if (type == "line")
	{
		return std::make_unique<Line>(id, color, params);
	}

	if (type == "text")
	{
		return std::make_unique<TextShape>(id, color, params);
	}

	throw std::invalid_argument("Unknown shape type: " + type);
}

void ShapeCreator::ChangeShapeType(
	IShape* shape,
	const std::string& newType,
	const std::vector<std::string>& params)
{
	const std::string id = shape->GetId();
	const Color color = shape->GetColor();

	const auto tempShape = CreateShape(id, color.ToString(), newType, params);
	shape->ChangeParameters(tempShape.get());
}