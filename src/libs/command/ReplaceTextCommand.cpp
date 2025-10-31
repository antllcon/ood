#include "ReplaceTextCommand.h"

ReplaceTextCommand::ReplaceTextCommand(std::shared_ptr<IParagraph> paragraph, const std::string& newText)
	: m_paragraph(std::move(paragraph))
	, m_newText(newText)
{
}

void ReplaceTextCommand::DoExecute()
{
	if (!m_isExecuted)
	{
		m_oldText = m_paragraph->GetText();
	}

	m_paragraph->SetText(m_newText);
}

void ReplaceTextCommand::DoUnexecute()
{
	m_paragraph->SetText(m_oldText);
}

bool ReplaceTextCommand::TryToMerge(const ICommand& nextCommand)
{
	if (const auto* other = dynamic_cast<const ReplaceTextCommand*>(&nextCommand))
	{
		if (other->m_paragraph == m_paragraph)
		{
			m_newText = other->m_newText;
			return true;
		}
	}

	return false;
}