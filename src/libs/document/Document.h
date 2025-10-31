#pragma once

#include "IDocument.h"
#include "command/CommandHistory.h"
#include "resource/IResourceManager.h"

#include <set>
#include <vector>

class Document final : public IDocument
{
public:
	explicit Document(const std::string& title, std::shared_ptr<IResourceManager> resourceManager);
	~Document() override = default;

	void Undo() override;
	void Redo() override;

	bool CanUndo() const override;
	bool CanRedo() const override;

	size_t GetItemsCount() const override;
	void Save(const Path& path, const IExportStrategy& exporter) const override;

	std::string GetTitle() const override;
	void SetTitle(const std::string& title) override;

	void DeleteItem(size_t index) override;
	DocumentItem& GetItem(size_t index) override;
	const ConstDocumentItem& GetItem(size_t index) const override;

	std::shared_ptr<IParagraph> InsertParagraph(const std::string& text, std::optional<size_t> position = std::nullopt) override;
	std::shared_ptr<IImage> InsertImage(const Path& path, int width, int height, std::optional<size_t> position = std::nullopt) override;
private:
	void CheckPosition(std::optional<size_t> position) const;
	void CheckIndex(size_t index) const;

	std::string m_title;
	std::vector<DocumentItem> m_items;
	std::set<Path> m_markedForDelete;
	std::shared_ptr<IResourceManager> m_resourceManager;
	CommandHistory m_history;
};