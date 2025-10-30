#include "HTMLExportStrategy.h"

#include "document/IDocument.h"
#include "documentItem/ConstDocumentItem.h"
#include "image/IImage.h"
#include "paragraph/IParagraph.h"

#include <fstream>
#include <sstream>
#include <stdexcept>

namespace
{
void AssertIsFileExist(const std::ostream& file)
{
	if (!file)
	{
		throw std::runtime_error("Cannot open file for writing");
	}
}

} // namespace

void HTMLExportStrategy::Export(const IDocument& document, const Path& outputPath) const
{
	std::ofstream outFile(outputPath);
	AssertIsFileExist(outFile);

	outFile << GenerateHTMLHeader(document.GetTitle());

	for (size_t i = 0; i < document.GetItemsCount(); ++i)
	{
		const ConstDocumentItem& item = document.GetItem(i);

		if (auto paragraph = item.GetParagraph())
		{
			outFile << GenerateParagraphHTML(paragraph->GetText());
		}

		if (auto image = item.GetImage())
		{
			outFile << GenerateImageHTML(image);
		}
	}

	outFile << GenerateHTMLFooter();
}

std::string HTMLExportStrategy::EscapeHTML(const std::string& text)
{
	std::ostringstream oss;
	for (char c : text)
	{
		switch (c)
		{
		case '&':
			oss << "&amp;";
			break;
		case '<':
			oss << "&lt;";
			break;
		case '>':
			oss << "&gt;";
			break;
		case '"':
			oss << "&quot;";
			break;
		case '\'':
			oss << "&apos;";
			break;
		default:
			oss << c;
			break;
		}
	}

	return oss.str();
}

std::string HTMLExportStrategy::GenerateHTMLHeader(const std::string& title)
{
	const std::string escapedTitle = EscapeHTML(title);

	std::ostringstream oss;
	oss << "<!DOCTYPE html>\n";
	oss << "<html>\n";
	oss << "<head>\n";
	oss << "  <meta charset=\"UTF-8\">\n";
	oss << "  <title>" << escapedTitle << "</title>\n";
	oss << "</head>\n";
	oss << "<body>\n";
	oss << "  <h1>" << escapedTitle << "</h1>\n";

	return oss.str();
}

std::string HTMLExportStrategy::GenerateHTMLFooter() noexcept
{
	return "</body>\n</html>\n";
}

std::string HTMLExportStrategy::GenerateParagraphHTML(const std::string& text)
{
	return "  <p>" + EscapeHTML(text) + "</p>\n";
}

std::string HTMLExportStrategy::GenerateImageHTML(const std::shared_ptr<const IImage>& image)
{
	const std::string relativePath = image->GetPath().generic_string();

	std::ostringstream oss;
	oss << "  <img src=\"" << EscapeHTML(relativePath) << "\""
		<< " width=\"" << image->GetWidth() << "\""
		<< " height=\"" << image->GetHeight() << "\">\n";

	return oss.str();
}