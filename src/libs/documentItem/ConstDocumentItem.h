#pragma once
#include <memory>

class IImage;
class IParagraph;

class ConstDocumentItem
{
public:
	virtual ~ConstDocumentItem() = default;

	virtual std::shared_ptr<const IImage> GetImage() const = 0;
	virtual std::shared_ptr<const IParagraph> GetParagraph() const = 0;
};