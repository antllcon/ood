#pragma once
#include "ICommand.h"
#include "document/Document.h"

#include <string>

class SetTitleCommand final : public ICommand
{
public:
	explicit SetTitleCommand(std::shared_ptr<Document> document, const std::string& newTitle);

	void Execute() override;
	void Unexecute() override;
	bool TryToMerge(const ICommand& nextCommand) override;

private:
	std::shared_ptr<Document> m_document;
	std::string m_newTitle;
	std::string m_oldTitle;
	bool m_executedOnce = false;
};