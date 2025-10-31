#pragma once
#include "ICommand.h"
#include "paragraph/IParagraph.h"
#include <string>
#include <memory>

class ReplaceTextCommand final : public ICommand
{
public:
	explicit ReplaceTextCommand(std::shared_ptr<IParagraph> paragraph, const std::string& newText);

	void Execute() override;
	void Unexecute() override;
	bool TryToMerge(const ICommand& nextCommand) override;

private:
	std::shared_ptr<IParagraph> m_paragraph;
	std::string m_newText;
	std::string m_oldText;
	bool m_executedOnce = false;
};