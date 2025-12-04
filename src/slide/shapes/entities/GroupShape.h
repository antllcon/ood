#pragma once
#include "shapes/interfaces/IShape.h"
#include <memory>
#include <vector>

class GroupFillStyle;
class GroupLineStyle;

class GroupShape
	: public IShape
	, public std::enable_shared_from_this<GroupShape>
{
public:
	GroupShape();

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
	std::shared_ptr<GroupShape> GetComposite() override;

private:
	std::vector<std::shared_ptr<IShape>> m_shapes;
	std::shared_ptr<GroupLineStyle> m_line;
	std::shared_ptr<GroupFillStyle> m_fill;
};
