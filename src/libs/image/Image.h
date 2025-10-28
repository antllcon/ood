#pragma once

#include "IImage.h"

class Image final : public IImage
{
public:
	constexpr static unsigned int MIN_DIMENSION = 0;
	constexpr static unsigned int MAX_DIMENSION = 10000;

	Image(const std::string& path, unsigned int width, unsigned int height);
	~Image() override = default;

	const std::string& GetPath() const override;
	unsigned int GetWidth() const override;
	unsigned int GetHeight() const override;
	void Resize(unsigned width, unsigned height) override;

private:
	std::string m_path;
	unsigned int m_width = MIN_DIMENSION;
	unsigned int m_height = MIN_DIMENSION;
};