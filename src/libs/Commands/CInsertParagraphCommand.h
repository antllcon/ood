#pragma once
#include "../ICommand.h"
#include "../IDocument.h"
#include <optional>
#include <string>

class CInsertParagraphCommand : public ICommand
{
public:
	CInsertParagraphCommand(
		IDocument& document,
		const std::string& text,
		std::optional<size_t> position);

	void Execute() override;
	void Unexecute() override;

private:
	IDocument& m_document;
	std::string m_text;
	std::optional<size_t> m_position;

	// Сохраняем позицию, по которой реально произошла вставка,
	// чтобы корректно выполнить Unexecute
	size_t m_insertedPosition;
};
