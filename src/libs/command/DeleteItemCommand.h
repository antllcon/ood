#pragma once
#include "ICommand.h"
#include "documentItem/DocumentItem.h"
#include "resource/IResourceManager.h"
#include <memory>
#include <optional>
#include <vector>

class DeleteItemCommand final : public ICommand
{
public:
	DeleteItemCommand(std::vector<DocumentItem>& items, std::shared_ptr<IResourceManager> resourceManager, size_t position);
	~DeleteItemCommand() override;

protected:
	void DoExecute() override;
	void DoUnexecute() override;
	std::shared_ptr<IImage> GetImageFromItem();

private:
	std::vector<DocumentItem>& m_items;
	std::shared_ptr<IResourceManager> m_resourceManager;
	size_t m_position;
	std::optional<DocumentItem> m_deletedItem;
};