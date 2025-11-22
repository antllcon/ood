#pragma once
#include "Common.h"
#include "ICanvas.h"
#include <optional>
#include <memory>

class IShape;

class IShapes
{
public:
	virtual ~IShapes() = default;

	virtual size_t GetShapesCount() const = 0;
	virtual void InsertShape(std::shared_ptr<IShape> shape, size_t position) = 0;
	virtual std::shared_ptr<IShape> GetShapeAt(size_t position) = 0;
	virtual void RemoveShapeAt(size_t position) = 0;
};

class IShape
{
public:
	virtual ~IShape() = default;

	virtual void Draw(ICanvas& canvas) = 0;
	virtual Frame GetFrame() const = 0;
	virtual void SetFrame(double x1, double y1, double x2, double y2) = 0;

	virtual std::optional<LineStyle> GetLineStyle() const = 0;
	virtual std::optional<FillStyle> GetFillStyle() const = 0;

	virtual void SetLineStyle(bool isEnabled, RgbaColor color, double width = 1.0) = 0;
	virtual void SetFillStyle(bool isEnabled, RgbaColor color) = 0;

	virtual std::shared_ptr<IShapes> GetShapesGroup() = 0;
	virtual void SetParent(IShapes* parent) = 0;
};