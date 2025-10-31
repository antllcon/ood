#pragma once
#include "InsertItemCommand.h"
#include "paragraph/IParagraph.h"

class InsertParagraphCommand final : public InsertItemCommand
{
public:
	InsertParagraphCommand(std::vector<DocumentItem>& items, std::shared_ptr<IParagraph> paragraph, std::optional<size_t> position)
		: InsertItemCommand(items, DocumentItem(std::move(paragraph)), position)
	{
	}
};