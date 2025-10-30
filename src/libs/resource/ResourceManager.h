#pragma once

#include <filesystem>
#include <set>

using Path = std::filesystem::path;

class ResourceManager
{
public:
	explicit ResourceManager(Path imagesDirectory);
	~ResourceManager() = default;

	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;

	Path CopyImage(const Path& sourcePath) const;
	void SaveImagesTo(const Path& targetDirectory) const;
	void MarkForDeletion(const Path& path);
	void UnmarkForDeletion(const Path& path);
	void Cleanup();

private:
	Path m_imagesDirectory;
	std::set<Path> m_markedForDeletion;
};