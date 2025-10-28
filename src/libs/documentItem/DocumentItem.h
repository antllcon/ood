#pragma once

#include "ConstDocumentItem.h"

#include <memory>

class IImage;
class IParagraph;

class DocumentItem final : public ConstDocumentItem
{
public:
	explicit DocumentItem(std::shared_ptr<IImage> image);
	explicit DocumentItem(std::shared_ptr<IParagraph> paragraph);

	std::shared_ptr<const IImage> GetImage() const override;
	std::shared_ptr<const IParagraph> GetParagraph() const override;

	std::shared_ptr<IImage> GetImage();
	std::shared_ptr<IParagraph> GetParagraph();

private:
	std::shared_ptr<IParagraph> m_paragraph;
	std::shared_ptr<IImage> m_image;
};