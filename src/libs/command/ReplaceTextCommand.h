#pragma once
#include "ICommand.h"
#include "paragraph/IParagraph.h"
#include <string>
#include <memory>

class ReplaceTextCommand final : public ICommand
{
public:
	explicit ReplaceTextCommand(std::shared_ptr<IParagraph> paragraph, const std::string& newText);
	~ReplaceTextCommand() override = default;

	bool TryToMerge(const ICommand& nextCommand) override;

protected:
	void DoExecute() override;
	void DoUnexecute() override;

private:
	std::shared_ptr<IParagraph> m_paragraph;
	std::string m_newText;
	std::string m_oldText;
};