#include "ConsoleEditor.h"
#include "CommandParser.h"
#include "export/HTMLExportStrategy.h"
#include "image/IImage.h"
#include "paragraph/IParagraph.h"

namespace
{
void AsssertIsDocumentExist(const std::unique_ptr<IDocument>& document)
{
	if (!document)
	{
		throw std::invalid_argument("Document cannot be null");
	}
}
} // namespace

ConsoleEditor::ConsoleEditor(std::unique_ptr<IDocument> document, std::istream& in, std::ostream& out)
	: m_document(std::move(document))
	, m_in(in)
	, m_out(out)
{
	AsssertIsDocumentExist(m_document);
}

void ConsoleEditor::Run()
{
	m_isRunning = true;
	std::string inputLine;

	PrintHelp();

	while (m_isRunning)
	{
		m_out << "> ";
		if (!std::getline(m_in, inputLine))
		{
			m_isRunning = false;
			continue;
		}

		if (!inputLine.empty())
		{
			ProcessCommand(inputLine);
		}
	}
}

void ConsoleEditor::ProcessCommand(const std::string& input)
{
	auto tokens = CommandParser::Tokenize(input);
	if (tokens.empty())
	{
		return;
	}

	const std::string& command = tokens[0];
	std::vector args(tokens.begin() + 1, tokens.end());

	try
	{
		if (command == "InsertParagraph")
		{
			HandleInsertParagraph(args);
		}
		else if (command == "InsertImage")
		{
			HandleInsertImage(args);
		}
		else if (command == "SetTitle")
		{
			HandleSetTitle(args);
		}
		else if (command == "List")
		{
			HandleList();
		}
		else if (command == "DeleteItem")
		{
			HandleDeleteItem(args);
		}
		else if (command == "ReplaceText")
		{
			HandleReplaceText(args);
		}
		else if (command == "ResizeImage")
		{
			HandleResizeImage(args);
		}
		else if (command == "Save")
		{
			HandleSave(args);
		}
		else if (command == "Help")
		{
			PrintHelp();
		}
		else if (command == "Exit")
		{
			m_isRunning = false;
		}
		// TODO: else if (command == "Undo") ...
		// TODO: else if (command == "Redo") ...
		else
		{
			throw std::invalid_argument("Command not recognised");
		}
	}
	catch (const std::exception& _)
	{
	}
}

void ConsoleEditor::HandleInsertParagraph(const std::vector<std::string>& args) const
{
	if (args.size() < 2)
	{
		throw std::invalid_argument("Usage: InsertParagraph <pos|end> <text...>");
	}

	auto pos = CommandParser::ParsePosition(args[0], m_document->GetItemsCount());
	std::string text = CommandParser::Join(args, 1);

	m_document->InsertParagraph(text, pos);
	m_out << "Paragraph inserted.\n";
}

void ConsoleEditor::HandleInsertImage(const std::vector<std::string>& args) const
{
	if (args.size() != 4)
	{
		throw std::invalid_argument("Usage: InsertImage <pos|end> <width> <height> <path>");
	}

	auto pos = CommandParser::ParsePosition(args[0], m_document->GetItemsCount());
	auto dims = CommandParser::ParseDimensions(args[1], args[2]);
	Path path(args[3]);

	m_document->InsertImage(path, dims.first, dims.second, pos);
	m_out << "Image inserted.\n";
}

void ConsoleEditor::HandleSetTitle(const std::vector<std::string>& args) const
{
	if (args.empty())
	{
		throw std::invalid_argument("Usage: SetTitle <title...>");
	}

	m_document->SetTitle(CommandParser::Join(args, 0));
	m_out << "Title set.\n";
}

void ConsoleEditor::HandleDeleteItem(const std::vector<std::string>& args) const
{
	if (args.size() != 1)
	{
		throw std::invalid_argument("Usage: DeleteItem <pos>");
	}

	size_t pos = std::stoul(args[0]);
	m_document->DeleteItem(pos);
	m_out << "Item deleted.\n";
}

void ConsoleEditor::HandleReplaceText(const std::vector<std::string>& args) const
{
	if (args.size() < 2)
	{
		throw std::invalid_argument("Usage: ReplaceText <pos> <text...>");
	}

	size_t pos = std::stoul(args[0]);
	std::string text = CommandParser::Join(args, 1);

	DocumentItem& item = m_document->GetItem(pos);
	auto paragraph = item.GetParagraph();

	if (!paragraph)
	{
		throw std::invalid_argument(
			"Item at position " + args[0] + " is not a paragraph.");
	}

	paragraph->SetText(text); // (Пока нет Undo)
	m_out << "Text replaced.\n";
}

void ConsoleEditor::HandleResizeImage(const std::vector<std::string>& args) const
{
	if (args.size() != 3)
	{
		throw std::invalid_argument("Usage: ResizeImage <pos> <width> <height>");
	}

	size_t pos = std::stoul(args[0]);
	auto dims = CommandParser::ParseDimensions(args[1], args[2]);

	DocumentItem& item = m_document->GetItem(pos);
	auto image = item.GetImage();

	if (!image)
	{
		throw std::invalid_argument(
			"Item at position " + args[0] + " is not an image.");
	}

	image->Resize(dims.first, dims.second); // (Пока нет Undo)
	m_out << "Image resized.\n";
}

void ConsoleEditor::HandleList() const
{
	m_out << "Title: " << m_document->GetTitle() << "\n";

	const size_t count = m_document->GetItemsCount();
	if (count == 0)
	{
		m_out << "(Document is empty)\n";
		return;
	}

	for (size_t i = 0; i < count; ++i)
	{
		m_out << i << ". ";

		const ConstDocumentItem& item = m_document->GetItem(i);

		if (auto p = item.GetParagraph())
		{
			m_out << "Paragraph: " << p->GetText() << "\n";
		}
		else if (auto img = item.GetImage())
		{
			m_out << "Image: " << img->GetWidth() << " "
				  << img->GetHeight() << " "
				  << img->GetPath().generic_string()
				  << "\n";
		}
	}
}

void ConsoleEditor::HandleSave(const std::vector<std::string>& args) const
{
	if (args.size() != 1)
	{
		throw std::invalid_argument("Usage: Save <path>");
	}

	Path savePath(args[0]);

	HTMLExportStrategy exporter;
	m_document->Save(savePath, exporter);

	m_out << "Document saved to " << savePath.string() << "\n";
}

void ConsoleEditor::PrintHelp() const
{
	m_out << "--- C++ Document Editor ---\n";
	m_out << "Commands:\n";
	m_out << "  InsertParagraph <pos|end> <text...>		- Insert paragraph\n";
	m_out << "  InsertImage <pos|end> <w> <h> <path>	- Insert image\n";
	m_out << "  SetTitle <title...>						- Set document title\n";
	m_out << "  DeleteItem <pos>						- Delete item at position\n";
	m_out << "  ReplaceText <pos> <text...>				- Replace paragraph text\n";
	m_out << "  ResizeImage <pos> <w> <h>				- Resize image\n";
	m_out << "  List									- List document items\n";
	m_out << "  Save <path.html>						- Save document as HTML\n";
	// m_out << "  Undo\n";
	// m_out << "  Redo\n";
	m_out << "  Help									- Show this help\n";
	m_out << "  Exit									- Quit the editor\n";
}