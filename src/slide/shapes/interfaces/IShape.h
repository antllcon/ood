#pragma once
#include "canvas/ICanvas.h"
#include "common/Frame.h"
#include <memory>

class GroupShape;
class ILineStyle;
class IFillStyle;

class IShape
{
public:
	virtual void Draw(ICanvas& canvas) const = 0;
	virtual ~IShape() = default;

	virtual Frame GetFrame() const = 0;
	virtual void SetFrame(const Frame& frame) = 0;

	virtual std::shared_ptr<ILineStyle> GetLineStyle() const = 0;
	virtual std::shared_ptr<IFillStyle> GetFillStyle() const = 0;

	virtual size_t GetShapeCount() const = 0;
	virtual std::shared_ptr<IShape> GetShapeAt(size_t index) const = 0;
	virtual void AddShape(std::shared_ptr<IShape> shape) = 0;
	virtual void RemoveShapeAt(size_t index) = 0;

	virtual std::unique_ptr<IShape> Clone() const = 0;
	virtual std::shared_ptr<GroupShape> GetComposite()
	{
		return nullptr;
	}
};