#pragma once
#include "ICommand.h"
#include "document/Document.h"

#include <string>

class SetTitleCommand final : public ICommand
{
public:
	explicit SetTitleCommand(std::string& targetTitle, const std::string& newTitle);
	~SetTitleCommand() override = default;

	bool TryToMerge(const ICommand& nextCommand) override;

protected:
	void DoExecute() override;
	void DoUnexecute() override;

private:
	std::string& m_targetTitle;
	std::string m_newTitle;
	std::string m_oldTitle;
};