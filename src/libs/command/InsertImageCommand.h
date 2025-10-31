#pragma once
#include "InsertItemCommand.h"
#include "image/IImage.h"
#include "resource/IResourceManager.h"

class InsertImageCommand final : public InsertItemCommand
{
public:
	InsertImageCommand(std::vector<DocumentItem>& items,
		std::shared_ptr<IImage> image,
		std::shared_ptr<IResourceManager> resourceManager,
		std::optional<size_t> position);

protected:
	void MarkResource() override;
	void UnmarkResource() override;

private:
	std::shared_ptr<IResourceManager> m_resourceManager;
	std::shared_ptr<IImage> m_image;
};