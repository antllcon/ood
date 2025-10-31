#include "InsertItemCommand.h"

InsertItemCommand::InsertItemCommand(std::vector<DocumentItem>& items, DocumentItem item, std::optional<size_t> position)
	: m_items(items)
	, m_item(std::move(item))
{
	m_position = position.value_or(m_items.size());
}

void InsertItemCommand::Execute()
{
	UnmarkResource();
	m_items.insert(m_items.begin() + m_position, std::move(m_item));
}

void InsertItemCommand::Unexecute()
{
	m_item = std::move(m_items[m_position]);
	m_items.erase(m_items.begin() + m_position);
	MarkResource();
}