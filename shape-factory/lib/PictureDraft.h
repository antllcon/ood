#include "Shape.h"
#include <memory>
#include <vector>

class IPictureDraft
{
public:
	virtual ~IPictureDraft() = default;

	virtual size_t GetShapeCount() const = 0;
	virtual const Shape& GetShape(size_t index) const = 0;
};

class PictureDraft final : public IPictureDraft
{
public:
	using Shapes = std::vector<std::unique_ptr<Shape>>;

	size_t GetShapeCount() const override
	{
		return m_shapes.size();
	}

	const Shape& GetShape(size_t index) const override
	{
		return *m_shapes.at(index);
	}

	void AddShape(std::unique_ptr<Shape> shape)
	{
		m_shapes.push_back(std::move(shape));
	}

	bool IsEmpty() const
	{
		return m_shapes.empty();
	}

private:
	Shapes m_shapes;
};
