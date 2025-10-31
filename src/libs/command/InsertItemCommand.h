#pragma once
#include "ICommand.h"
#include "documentItem/DocumentItem.h"
#include <optional>
#include <vector>

class InsertItemCommand : public ICommand
{
public:
	InsertItemCommand(std::vector<DocumentItem>& items, DocumentItem item, std::optional<size_t> position);
	~InsertItemCommand() override = default;

protected:
	void DoExecute() override;
	void DoUnexecute() override;

	virtual void MarkResourceForDeletion()
	{
	}
	virtual void UnmarkResourceForDeletion()
	{
	}
	virtual void CleanupResource()
	{
	}

private:
	std::vector<DocumentItem>& m_items;
	DocumentItem m_item;
	size_t m_position;
};