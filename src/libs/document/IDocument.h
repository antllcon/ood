#pragma once
#include "documentItem/ConstDocumentItem.h"
#include "documentItem/DocumentItem.h"
#include "export/IExportStrategy.h"

#include <filesystem>
#include <memory>
#include <optional>
#include <string>

using Path = std::filesystem::path;

class IDocument
{
public:
	virtual ~IDocument() = default;

	IDocument(const IDocument&) = delete;
	IDocument& operator=(const IDocument&) = delete;

	// virtual void Undo() = 0;
	// virtual void Redo() = 0;
	//
	// virtual bool CanUndo() const = 0;
	// virtual bool CanRedo() const = 0;

	virtual size_t GetItemsCount() const = 0;
	virtual void Save(const Path& path, const IExportStrategy& exporter) const = 0;

	virtual std::string GetTitle() const = 0;
	virtual void SetTitle(const std::string& title) = 0;

	virtual void DeleteItem(size_t index) = 0;
	virtual DocumentItem& GetItem(size_t index) = 0;
	virtual const ConstDocumentItem& GetItem(size_t index) const = 0;

	virtual std::shared_ptr<IParagraph> InsertParagraph(const std::string& text, std::optional<size_t> position = std::nullopt) = 0;
	virtual std::shared_ptr<IImage> InsertImage(const Path& path, int width, int height, std::optional<size_t> position = std::nullopt) = 0;

protected:
	IDocument() = default;
};