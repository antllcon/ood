#include "SetTitleCommand.h"

SetTitleCommand::SetTitleCommand(std::string& targetTitle, const std::string& newTitle)
	: m_targetTitle(targetTitle)
	, m_newTitle(newTitle)
{
}

void SetTitleCommand::DoExecute()
{
	if (!m_isExecuted)
	{
		m_oldTitle = m_targetTitle;
	}

	m_targetTitle = m_newTitle;
}

void SetTitleCommand::DoUnexecute()
{
	m_targetTitle = m_oldTitle;
}

bool SetTitleCommand::TryToMerge(const ICommand& nextCommand)
{
	if (const auto* other = dynamic_cast<const SetTitleCommand*>(&nextCommand))
	{
		m_newTitle = other->m_newTitle;
		return true;
	}

	return false;
}