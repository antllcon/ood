#pragma once
#include "ShapeFactory.h"
#include <Painter.h>
#include <memory>
#include <string>

class IShapeFactory;
class IDesigner
{
public:
	virtual ~IDesigner() = default;

	virtual std::unique_ptr<IPictureDraft> CreateDraft(std::istream& strm) = 0;
};

class Designer final : public IDesigner
{
public:
	explicit Designer(IShapeFactory& factory)
		: m_factory(factory)
	{
	}

	std::unique_ptr<IPictureDraft> CreateDraft(std::istream& strm) override
	{
		auto draft = std::make_unique<PictureDraft>();
		std::string line;

		while (std::getline(strm, line))
		{
			if (line.empty())
			{
				continue;
			}

			auto shape = m_factory.CreateShape(line);

			if (shape)
			{
				draft->AddShape(std::move(shape));
			}
		}

		return draft;
	}

private:
	IShapeFactory& m_factory;
};