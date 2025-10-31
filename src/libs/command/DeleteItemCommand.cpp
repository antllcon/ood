#include "DeleteItemCommand.h"
#include "image/IImage.h"

DeleteItemCommand::DeleteItemCommand(
	std::vector<DocumentItem>& items,
	std::shared_ptr<IResourceManager> resourceManager,
	size_t position)
	: m_items(items)
	, m_resourceManager(std::move(resourceManager))
	, m_position(position)
	, m_deletedItem(std::nullopt)
{
}

void DeleteItemCommand::Execute()
{
	m_deletedItem.emplace(std::move(m_items[m_position]));
	m_items.erase(m_items.begin() + m_position);

	if (auto image = m_deletedItem->GetImage())
	{
		m_resourceManager->MarkForDeletion(image->GetPath());
	}
}

void DeleteItemCommand::Unexecute()
{
	if (auto image = m_deletedItem->GetImage())
	{
		m_resourceManager->UnmarkForDeletion(image->GetPath());
	}

	m_items.insert(m_items.begin() + m_position, std::move(*m_deletedItem));
	m_deletedItem.reset();
}