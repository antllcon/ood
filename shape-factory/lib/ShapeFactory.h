#pragma once
#include <Designer.h>
#include <memory>
#include <stdexcept>
#include <string>

class IShapeFactory
{
public:
	virtual ~IShapeFactory() = default;

	virtual std::unique_ptr<Shape> CreateShape(const std::string& descr) = 0;
};

class ShapeFactory final : public IShapeFactory
{
public:
	std::unique_ptr<Shape> CreateShape(const std::string& descr) override
	{
		std::stringstream ss(descr);
		std::string shapeType;
		ss >> shapeType;

		if (shapeType == "rectangle")
		{
			return CreateRectangle(ss);
		}
		if (shapeType == "triangle")
		{
			return CreateTriangle(ss);
		}
		if (shapeType == "ellipse")
		{
			return CreateEllipse(ss);
		}

		return nullptr;
	}

private:
	Color ParseColor(const std::string& colorStr)
	{

		auto it = colorMap.find(colorStr);
		if (it == colorMap.end())
		{
			throw std::invalid_argument("Unknown color");
		}

		return it->second;
	}

	std::unique_ptr<Shape> CreateRectangle(std::stringstream& ss)
	{
		std::string colorStr;
		Point leftTop, rightBottom;

		ss >> colorStr >> leftTop.x >> leftTop.y >> rightBottom.x >> rightBottom.y;

		if (ss.fail())
		{
			return nullptr;
		}

		try
		{
			Color color = ParseColor(colorStr);
			return std::make_unique<Rectangle>(color, leftTop, rightBottom);
		}
		catch (const std::invalid_argument&)
		{
			return nullptr;
		}
	}

	std::unique_ptr<Shape> CreateTriangle(std::stringstream& ss)
	{
		std::string colorStr;
		Point v1, v2, v3;

		ss >> colorStr >> v1.x >> v1.y >> v2.x >> v2.y >> v3.x >> v3.y;

		if (ss.fail())
		{
			return nullptr;
		}

		try
		{
			Color color = ParseColor(colorStr);
			return std::make_unique<Triangle>(color, v1, v2, v3);
		}
		catch (const std::invalid_argument&)
		{
			return nullptr;
		}
	}

	std::unique_ptr<Shape> CreateEllipse(std::stringstream& ss)
	{
		std::string colorStr;
		Point center;
		int hr, vr;

		ss >> colorStr >> center.x >> center.y >> hr >> vr;

		if (ss.fail())
		{
			return nullptr;
		}

		try
		{
			Color color = ParseColor(colorStr);
			return std::make_unique<Ellipse>(color, center, hr, vr);
		}
		catch (const std::invalid_argument&)
		{
			return nullptr;
		}
	}
};
