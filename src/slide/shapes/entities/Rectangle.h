#pragma once
#include "shapes/interfaces/IFillStyle.h"
#include "shapes/interfaces/ILineStyle.h"
#include "shapes/interfaces/IShape.h"
#include "shapes/styles/SimpleFillStyle.h"
#include "shapes/styles/SimpleLineStyle.h"
#include <memory>

class Rectangle : public IShape
{
public:
	explicit Rectangle(const Frame& frame);

	void Draw(ICanvas& canvas) const override;
	Frame GetFrame() const override;
	void SetFrame(const Frame& frame) override;

	std::shared_ptr<ILineStyle> GetLineStyle() const override;
	std::shared_ptr<IFillStyle> GetFillStyle() const override;

	size_t GetShapeCount() const override;
	std::shared_ptr<IShape> GetShapeAt(size_t index) const override;
	void AddShape(std::shared_ptr<IShape> shape) override;
	void RemoveShapeAt(size_t index) override;

	std::unique_ptr<IShape> Clone() const override;

private:
	Frame m_frame;
	std::shared_ptr<SimpleLineStyle> m_line;
	std::shared_ptr<SimpleFillStyle> m_fill;
};