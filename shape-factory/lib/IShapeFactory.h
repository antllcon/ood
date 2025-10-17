#pragma once

#include <memory>
#include "Shape.h"

class IShapeFactory
{
public:
	virtual ~IShapeFactory() = default;

	virtual std::unique_ptr<Shape> CreateShape(const std::string& descr) = 0;
};