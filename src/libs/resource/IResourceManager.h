#pragma once
#include <filesystem>

using Path = std::filesystem::path;

class IResourceManager
{
public:
	virtual ~IResourceManager() = default;

	IResourceManager(const IResourceManager&) = delete;
	IResourceManager& operator=(const IResourceManager&) = delete;

	virtual Path CopyImage(const Path& sourcePath) const = 0;
	virtual void SaveImagesTo(const Path& targetDirectory) const = 0;
	virtual void MarkForDeletion(const Path& path) = 0;
	virtual void UnmarkForDeletion(const Path& path) = 0;
	virtual void Cleanup() = 0;

protected:
	IResourceManager() = default;
};