#pragma once

#include "IResourceManager.h"

#include <filesystem>
#include <set>

using Path = std::filesystem::path;

class ResourceManager final : public IResourceManager
{
public:
	explicit ResourceManager() = default;
	explicit ResourceManager(Path imagesDirectory);
	~ResourceManager() override = default;

	Path CopyImage(const Path& sourcePath) const override;
	void SaveImagesTo(const Path& targetDirectory) const override;
	void MarkForDeletion(const Path& path) override;
	void UnmarkForDeletion(const Path& path) override;
	void Cleanup() override;

private:
	Path m_imagesDirectory = Path("temp");
	std::set<Path> m_markedForDeletion;
};