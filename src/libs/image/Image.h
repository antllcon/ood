#pragma once

#include "IImage.h"

class Image final : public IImage
{
public:
	constexpr static unsigned int DEFAULT_SIZE = 64;
	constexpr static unsigned int MIN_DIMENSION = 1;
	constexpr static unsigned int MAX_DIMENSION = 10000;

	Image(const Path& path);
	Image(const Path& path, unsigned int width, unsigned int height);
	~Image() override = default;

	const Path& GetPath() const override;
	unsigned int GetWidth() const override;
	unsigned int GetHeight() const override;
	void Resize(unsigned width, unsigned height) override;

private:
	Path m_path;
	unsigned int m_width = MIN_DIMENSION;
	unsigned int m_height = MIN_DIMENSION;
};