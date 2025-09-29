#include "Picture.h"
#include <algorithm>
#include <stdexcept>

// TODO: вынести другие исключения
namespace
{
void AssertIsExistPointer(const IShape* ptr)
{
	if (ptr == nullptr)
	{
		throw std::invalid_argument("ShapePtr is null");
	}
}
} // namespace

IShape* Picture::GetShape(const std::string& id) const
{
	const auto it = m_lookup.find(id);
	return it != m_lookup.end() ? it->second : nullptr;
}

void Picture::AddShape(std::unique_ptr<IShape> shape)
{
	const std::string id = shape->GetId();

	if (m_lookup.contains(id))
	{
		throw std::invalid_argument("Shape with id " + id + " already exists");
	}

	IShape* shapePtr = shape.get();
	m_shapes.emplace_back(std::move(shape));
	m_lookup[id] = shapePtr;
}

void Picture::RemoveShape(const std::string& id)
{
	const auto it = m_lookup.find(id);
	if (it == m_lookup.end())
	{
		throw std::invalid_argument("Shape with id " + id + " not found");
	}

	IShape* shapeToRemove = it->second;
	m_lookup.erase(it);

	const auto vectorIt = std::ranges::find_if(m_shapes, [shapeToRemove](const std::unique_ptr<IShape>& shape) {
		return shape.get() == shapeToRemove;
	});

	if (vectorIt != m_shapes.end())
	{
		m_shapes.erase(vectorIt);
	}
}

void Picture::MoveShape(const std::string& id, const double dx, const double dy) const
{
	IShape* shape = GetShape(id);
	AssertIsExistPointer(shape);
	shape->Move(dx, dy);
}

void Picture::MoveAll(const double dx, const double dy) const
{
	for (const auto& shape : m_shapes)
	{
		AssertIsExistPointer(shape.get());
		shape->Move(dx, dy);
	}
}

void Picture::Draw(ICanvas* canvas) const
{
	for (const auto& shape : m_shapes)
	{
		AssertIsExistPointer(shape.get());
		shape->Draw(canvas);
	}
}

void Picture::DrawShape(const std::string& id, ICanvas* canvas) const
{
	IShape* shape = GetShape(id);
	AssertIsExistPointer(shape);
	shape->Draw(canvas);
}

std::vector<std::string> Picture::ListShapes() const
{
	std::vector<std::string> result;
	int index = 1;

	for (const auto& shape : m_shapes)
	{
		std::string info = std::to_string(index++) + " " + shape->GetType() + " " + shape->GetId() + " " + shape->GetColor().ToString();
		result.emplace_back(info);
	}

	return result;
}