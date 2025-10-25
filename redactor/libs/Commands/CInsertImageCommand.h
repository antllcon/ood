#pragma once
#include "../ICommand.h"
#include "../IDocument.h"

class CSetTitleCommand : public ICommand
{
public:
	CSetTitleCommand(IDocument& document, const std::string& newTitle);

	void Execute() override;
	void Unexecute() override;

private:
	IDocument& m_document;
	std::string m_newTitle;
	std::string m_oldTitle;
};
