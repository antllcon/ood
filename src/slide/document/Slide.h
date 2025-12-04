#pragma once
#include "canvas/IDrawable.h"
#include "shapes/interfaces/IShape.h"
#include <memory>
#include <vector>

class Slide final : public IDrawable
{
public:
	Slide() = default;
	void Draw(ICanvas& canvas) const override;

	size_t GetShapeCount() const;
	std::shared_ptr<IShape> GetShapeAt(size_t index) const;
	void AddShape(std::shared_ptr<IShape> shape);

private:
	std::vector<std::shared_ptr<IShape>> m_shapes;
};