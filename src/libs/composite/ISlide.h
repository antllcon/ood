#pragma once

#include <memory>
#include "Common.h"
#include "ICanvas.h"
#include "IShape.h"

class ISlide
{
public:
	virtual ~ISlide() = default;
	virtual double GetWidth() const = 0;
	virtual double GetHeight() const = 0;
	virtual void SetBackgroundColor(RgbaColor color) = 0;
	virtual void Draw(ICanvas& canvas) = 0;
	virtual void InsertShape(std::shared_ptr<IShape> shape, size_t position) = 0;
	// Для упрощения здесь мы используем тот же метод, но в C++ для группировки
	// лучше использовать отдельный метод, принимающий индексы
	virtual void InsertShapeGroup(const std::vector<size_t>& indexes) = 0;
};