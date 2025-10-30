#pragma once

#include "IExportStrategy.h"

#include <filesystem>
#include <memory>
#include <string>

using Path = std::filesystem::path;
class IDocument;
class IImage;

class HTMLExportStrategy final : public IExportStrategy
{
public:
	HTMLExportStrategy() = default;
	~HTMLExportStrategy() override = default;

	void Export(const IDocument& document, const Path& outputPath) const override;

private:
	static std::string EscapeHTML(const std::string& text);
	static std::string GenerateHTMLHeader(const std::string& title);
	static std::string GenerateHTMLFooter() noexcept;
	static std::string GenerateParagraphHTML(const std::string& text);
	static std::string GenerateImageHTML(const std::shared_ptr<const IImage>& image);
};