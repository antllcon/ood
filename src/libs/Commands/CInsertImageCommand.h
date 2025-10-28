#pragma once
#include "../ICommand.h"
#include "../IDocument.h"
#include "../stdafx.h"

class CInsertImageCommand : public ICommand
{
public:
	CInsertImageCommand(
		IDocument& document,
		const std::filesystem::path& path,
		int width,
		int height,
		std::optional<size_t> position);

	void Execute() override;
	void Unexecute() override;

private:
	IDocument& m_document;
	std::filesystem::path m_sourcePath;
	int m_width;
	int m_height;
	std::optional<size_t> m_position;

	size_t m_insertedPosition;
};
