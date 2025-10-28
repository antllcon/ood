#include "Paragraph.h"

Paragraph::Paragraph(const std::string& text)
	: m_text(text)
{
}

const std::string& Paragraph::GetText() const
{
	return m_text;
}

void Paragraph::SetText(const std::string& text)
{
	m_text = text;
}