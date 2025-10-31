#include "InsertImageCommand.h"

InsertImageCommand::InsertImageCommand(
	std::vector<DocumentItem>& items,
	std::shared_ptr<IImage> image,
	std::shared_ptr<IResourceManager> resourceManager,
	std::optional<size_t> position)
	: InsertItemCommand(items, DocumentItem(image), position)
	, m_resourceManager(std::move(resourceManager))
	, m_image(std::move(image))
{
}
InsertImageCommand::~InsertImageCommand()
{
	if (!m_isExecuted)
	{
		m_resourceManager->MarkForDeletion(m_image->GetPath());
		// Меченых удаляем...
		m_resourceManager->Cleanup();
	}
}

void InsertImageCommand::MarkResourceForDeletion()
{
	m_resourceManager->MarkForDeletion(m_image->GetPath());
}

void InsertImageCommand::UnmarkResourceForDeletion()
{
	m_resourceManager->UnmarkForDeletion(m_image->GetPath());
}

void InsertImageCommand::CleanupResource()
{
}