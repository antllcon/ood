#pragma once
#include "ICommand.h"
#include "documentItem/DocumentItem.h"
#include <optional>
#include <vector>

class InsertItemCommand : public ICommand
{
public:
	InsertItemCommand(std::vector<DocumentItem>& items, DocumentItem item, std::optional<size_t> position);

	void Execute() override;
	void Unexecute() override;

protected:
	virtual void MarkResource()
	{
	}

	virtual void UnmarkResource()
	{
	}

private:
	std::vector<DocumentItem>& m_items;
	DocumentItem m_item;
	size_t m_position;
};