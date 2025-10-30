#pragma once

#include <filesystem>

class IDocument;
using Path = std::filesystem::path;

class IExporterStrategy
{
public:
	virtual ~IExporterStrategy() = default;

	IExporterStrategy(const IExporterStrategy&) = delete;
	IExporterStrategy& operator=(const IExporterStrategy&) = delete;
	IExporterStrategy(IExporterStrategy&&) = delete;
	IExporterStrategy& operator=(IExporterStrategy&&) = delete;

	virtual void Export(const IDocument& document, const Path& outputPath) const = 0;

protected:
	IExporterStrategy() = default;
};