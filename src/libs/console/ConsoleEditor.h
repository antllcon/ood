#pragma once

#include "document/IDocument.h"
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class ConsoleEditor final
{
public:
	explicit ConsoleEditor(std::unique_ptr<IDocument> document, std::istream& in, std::ostream& out);
	~ConsoleEditor() = default;

	ConsoleEditor(const ConsoleEditor&) = delete;
	ConsoleEditor& operator=(const ConsoleEditor&) = delete;

	void Run();

private:
	void ProcessCommand(const std::string& input);

	void HandleInsertParagraph(const std::vector<std::string>& args) const;
	void HandleInsertImage(const std::vector<std::string>& args) const;
	void HandleSetTitle(const std::vector<std::string>& args) const;
	void HandleDeleteItem(const std::vector<std::string>& args) const;
	void HandleReplaceText(const std::vector<std::string>& args) const;
	void HandleResizeImage(const std::vector<std::string>& args) const;
	void HandleList() const;
	void HandleSave(const std::vector<std::string>& args) const;

	// TODO: HandleUndo/HandleRedo (когда IDocument их реализует)

	void PrintHelp() const;
	void PrintError(const std::string& message) const;

	std::unique_ptr<IDocument> m_document;
	std::istream& m_in;
	std::ostream& m_out;
	bool m_isRunning = false;
};