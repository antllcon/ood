#include "SetTitleCommand.h"

SetTitleCommand::SetTitleCommand(std::shared_ptr<Document> document, const std::string& newTitle)
	: m_document(std::move(document))
	, m_newTitle(newTitle)
{
}

void SetTitleCommand::Execute()
{
	if (!m_executedOnce)
	{
		m_oldTitle = m_document->GetTitle();
		m_executedOnce = true;
	}

	m_document->SetTitle(m_newTitle);
}

void SetTitleCommand::Unexecute()
{
	m_document->SetTitle(m_oldTitle);
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