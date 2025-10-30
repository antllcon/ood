#pragma once

#include <filesystem>

using Path = std::filesystem::path;

class IImage
{
public:
	virtual ~IImage() = default;

	IImage(const IImage&) = delete;
	IImage& operator=(const IImage&) = delete;

	virtual const Path& GetPath() const = 0;
	virtual unsigned int GetWidth() const = 0;
	virtual unsigned int GetHeight() const = 0;
	virtual void Resize(unsigned int width, unsigned int height) = 0;

protected:
	IImage() = default;
};