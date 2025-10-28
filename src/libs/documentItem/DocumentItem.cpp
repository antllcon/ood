#include "DocumentItem.h"

namespace
{
template <typename T>
void AssertIsPtrNotNull(std::shared_ptr<T> ptr)
{
	if (ptr.get() == nullptr)
	{
		throw std::invalid_argument("Ptr is null");
	}
}
}

DocumentItem::DocumentItem(std::shared_ptr<IImage> image)
	: m_image(std::move(image))
{
	AssertIsPtrNotNull(m_image);
}

DocumentItem::DocumentItem(std::shared_ptr<IParagraph> paragraph)
	: m_paragraph(std::move(paragraph))
{
	AssertIsPtrNotNull(m_paragraph);
}

std::shared_ptr<const IImage> DocumentItem::GetImage() const
{
	return m_image;
}

std::shared_ptr<const IParagraph> DocumentItem::GetParagraph() const
{
	return m_paragraph;
}

std::shared_ptr<IImage> DocumentItem::GetImage()
{
	return m_image;
}

std::shared_ptr<IParagraph> DocumentItem::GetParagraph()
{
	return m_paragraph;
}
