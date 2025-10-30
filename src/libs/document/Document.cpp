#include "Document.h"

#include "image/Image.h"
#include "paragraph/IParagraph.h"
#include "paragraph/Paragraph.h"

namespace
{
void AssertIsTitleExist(const std::string& title)
{
	if (title.empty())
	{
		throw std::invalid_argument("Title is empty");
	}
}

void AssertIsResourceManagerValid(const std::shared_ptr<IResourceManager>& resourceManager)
{
	if (!resourceManager)
	{
		throw std::invalid_argument("ResourceManager cannot be null");
	}
}
}

Document::Document(const std::string& title, std::shared_ptr<IResourceManager> resourceManager)
	: m_resourceManager(std::move(resourceManager))
{
	AssertIsResourceManagerValid(m_resourceManager);
	SetTitle(title);
}

size_t Document::GetItemsCount() const
{
	return m_items.size();
}

void Document::Save(const Path& path, const IExportStrategy& exporter) const
{
	exporter.Export(*this, path);
}

std::string Document::GetTitle() const
{
	return m_title;
}

void Document::SetTitle(const std::string& title)
{
	AssertIsTitleExist(title);
	m_title = title;
}

void Document::DeleteItem(size_t index)
{
	CheckIndex(index);
	DocumentItem& item = m_items[index];

	if (auto image = item.GetImage())
	{
		m_resourceManager->MarkForDeletion(image->GetPath());
	}

	m_items.erase(m_items.begin() + index);
}

DocumentItem& Document::GetItem(size_t index)
{
	CheckIndex(index);
	return m_items[index];
}

const ConstDocumentItem& Document::GetItem(size_t index) const
{
	CheckIndex(index);
	return m_items[index];
}

std::shared_ptr<IParagraph> Document::InsertParagraph(const std::string& text, std::optional<size_t> position)
{
	CheckPosition(position);
	auto paragraph = std::make_shared<Paragraph>(text);
	DocumentItem item(paragraph);

	size_t pos = position.value_or(m_items.size());
	m_items.insert(m_items.begin() + pos, std::move(item));
	return paragraph;
}

std::shared_ptr<IImage> Document::InsertImage(const Path& path, int width, int height, std::optional<size_t> position)
{
	CheckPosition(position);
	Path newPath = m_resourceManager->CopyImage(path);

	auto image = std::make_shared<Image>(newPath, width, height);
	DocumentItem item(image);

	size_t pos = position.value_or(m_items.size());
	m_items.insert(m_items.begin() + pos, std::move(item));
	return image;
}

void Document::CheckPosition(std::optional<size_t> position) const
{
	if (position.has_value() && position.value() > m_items.size())
	{
		throw std::out_of_range("Invalid insert position");
	}
}

void Document::CheckIndex(size_t index) const
{
	if (index >= m_items.size())
	{
		throw std::out_of_range("Invalid item index");
	}
}