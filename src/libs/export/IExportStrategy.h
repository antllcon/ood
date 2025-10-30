#pragma once

#include <filesystem>

class IDocument;
using Path = std::filesystem::path;

class IExportStrategy
{
public:
	virtual ~IExportStrategy() = default;

	IExportStrategy(const IExportStrategy&) = delete;
	IExportStrategy& operator=(const IExportStrategy&) = delete;
	IExportStrategy(IExportStrategy&&) = delete;
	IExportStrategy& operator=(IExportStrategy&&) = delete;

	virtual void Export(const IDocument& document, const Path& outputPath) const = 0;

protected:
	IExportStrategy() = default;
};