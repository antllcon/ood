#pragma once

#include "IShape.h"
#include "ISlide.h"
#include "ShapeGroup.h"
#include <algorithm>
#include <memory>
#include <vector>

class Slide : public ISlide
{
public:
	Slide(double w, double h)
		: m_width(w)
		, m_height(h)
	{
	}

	double GetWidth() const override
	{
		return m_width;
	}
	double GetHeight() const override
	{
		return m_height;
	}

	void SetBackgroundColor(RgbaColor color) override
	{
		m_bgColor = color;
	}

	void InsertShape(std::shared_ptr<IShape> shape, size_t position = std::numeric_limits<size_t>::max()) override
	{
		if (position >= m_shapes.size())
		{
			m_shapes.push_back(shape);
		}
		else
		{
			m_shapes.insert(m_shapes.begin() + position, shape);
		}
	}

	void InsertShapeGroup(const std::vector<size_t>& indexes) override
	{
		if (indexes.empty()) return;

		std::vector<size_t> sortedIdx = indexes;
		// Сортируем по убыванию, чтобы удаление не сбивало индексы
		std::sort(sortedIdx.rbegin(), sortedIdx.rend());

		auto group = std::make_shared<ShapeGroup>();

		// Вставляем в группу в обратном порядке (чтобы сохранить Z-order, нужно аккуратнее,
		// но для базовой логики достаточно забрать элементы)
		// В C# коде была логика сортировки. Здесь мы забираем элементы.

		// Нужно восстановить правильный порядок для вставки в группу (возрастающий)
		std::vector<std::shared_ptr<IShape>> tempShapes;
		for (size_t idx : sortedIdx)
		{
			if (idx < m_shapes.size())
			{
				tempShapes.push_back(m_shapes[idx]);
				m_shapes.erase(m_shapes.begin() + idx);
			}
		}
		// Возвращаем порядок к нормальному (так как мы шли с конца)
		std::ranges::reverse(tempShapes);

		for (const auto& s : tempShapes)
		{
			group->InsertShape(s, std::numeric_limits<size_t>::max());
		}

		// Вставляем группу на место самого последнего элемента (по индексу) из исходного набора
		size_t insertPos = sortedIdx.back(); // Это минимальный индекс, так как массив отсортирован по убыванию

		if (insertPos > m_shapes.size()) insertPos = m_shapes.size();
		m_shapes.insert(m_shapes.begin() + insertPos, group);
	}

	void Draw(ICanvas& canvas) override
	{
		// Background
		canvas.SetFillColor(m_bgColor);
		canvas.FillPolygon({{0, 0}, {m_width, 0}, {m_width, m_height}, {0, m_height}});

		for (const auto& shape : m_shapes)
		{
			shape->Draw(canvas);
		}
	}

private:
	double m_width;
	double m_height;
	RgbaColor m_bgColor{255, 255, 255, 1};
	std::vector<std::shared_ptr<IShape>> m_shapes;
};