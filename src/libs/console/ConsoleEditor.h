#pragma once

#include "document/IDocument.h"
#include <memory>
#include <string>
#include <vector>

class ConsoleEditor
{
public:
	explicit ConsoleEditor(std::unique_ptr<IDocument> document, std::istream& in, std::ostream& out);
	~ConsoleEditor() = default;

	ConsoleEditor(const ConsoleEditor&) = delete;
	ConsoleEditor& operator=(const ConsoleEditor&) = delete;

	void Run();

private:
	void ProcessCommand(const std::string& input);

	void HandleInsertParagraph(const std::vector<std::string>& args);
	void HandleInsertImage(const std::vector<std::string>& args) ;
	void HandleSetTitle(const std::vector<std::string>& args);
	void HandleDeleteItem(const std::vector<std::string>& args);
	void HandleReplaceText(const std::vector<std::string>& args);
	void HandleResizeImage(const std::vector<std::string>& args);
	void HandleUndo();
	void HandleRedo();

	void HandleSave(const std::vector<std::string>& args) const;
	void HandleList() const;
	void PrintHelp() const;
	static void PrintError(const std::string& message);

	std::unique_ptr<IDocument> m_document;
	std::istream& m_in;
	std::ostream& m_out;
	bool m_isRunning = false;
};