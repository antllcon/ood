#include "ResourceManager.h"
#include <iomanip>
#include <random>
#include <sstream>
#include <stdexcept>

namespace
{
void AssetIsFileExist(const Path& sourcePath)
{
	if (!std::filesystem::exists(sourcePath))
	{
		throw std::invalid_argument("Source file does not exist");
	}
}

std::string GenerateName(const Path& sourcePath)
{
	auto now = std::chrono::system_clock::now();
	auto time = std::chrono::system_clock::to_time_t(now);

	std::random_device rd;
	std::uniform_int_distribution<int> dis(0, 999);

	std::stringstream ss;
	ss << std::put_time(std::localtime(&time), "%Y%m%d-%H%M%S");
	ss << "_" << std::setw(3) << std::setfill('0') << dis(rd);
	return ss.str() + sourcePath.extension().string();
}

Path FindUniquePath(const Path& directory, const Path& sourcePath)
{
	std::string baseName = GenerateName(sourcePath);
	Path destPath = directory / baseName;

	int counter = 1;
	const std::string stem = destPath.stem().string();
	const std::string ext = destPath.extension().string();

	while (std::filesystem::exists(destPath))
	{
		const std::string nextName = stem + "_" + std::to_string(counter) + ext;
		destPath = directory / nextName;
		++counter;
	}

	return destPath;
}

} // namespace

ResourceManager::ResourceManager(Path imagesDirectory)
	: m_imagesDirectory(std::move(imagesDirectory))
{
	if (!std::filesystem::exists(m_imagesDirectory))
	{
		std::filesystem::create_directory(m_imagesDirectory);
	}
}

Path ResourceManager::CopyImage(const Path& sourcePath) const
{
	AssetIsFileExist(sourcePath);
	Path destPath = FindUniquePath(m_imagesDirectory, sourcePath);
	std::filesystem::copy(sourcePath, destPath);
	return destPath.filename();
}

void ResourceManager::MarkForDeletion(const Path& path)
{
	m_markedForDeletion.insert(m_imagesDirectory / path);
}

void ResourceManager::UnmarkForDeletion(const Path& path)
{
	m_markedForDeletion.erase(m_imagesDirectory / path);
}

void ResourceManager::Cleanup()
{
	for (const auto& path : m_markedForDeletion)
	{
		if (std::filesystem::exists(path))
		{
			std::filesystem::remove(path);
		}
	}

	m_markedForDeletion.clear();
}

void ResourceManager::SaveImagesTo(const Path& targetDirectory) const
{
	if (!std::filesystem::exists(targetDirectory))
	{
		std::filesystem::create_directory(targetDirectory);
	}

	for (const auto& entry : std::filesystem::directory_iterator(m_imagesDirectory))
	{
		if (!entry.is_regular_file())
		{
			continue;
		}

		if (!m_markedForDeletion.contains(entry.path()))
		{
			std::filesystem::copy(entry.path(),
				targetDirectory / entry.path().filename(),
				std::filesystem::copy_options::overwrite_existing);
		}
	}
}