#include "Image.h"
#include <stdexcept>

namespace
{
void AssertIsSizeValid(unsigned int number)
{
	if (number < Image::MIN_DIMENSION || Image::MAX_DIMENSION < number)
	{
		throw std::out_of_range("Invalid size");
	}
}

void AssertIsPathExist(const Path& path)
{
	if (path.empty())
	{
		throw std::invalid_argument("Path is empty");
	}
}
} // namespace

Image::Image(const Path& path, unsigned int width, unsigned int height)
	:m_path(path)
{
	AssertIsPathExist(path);
	Resize(width, height);
}

const Path& Image::GetPath() const
{
	return m_path;
}

unsigned int Image::GetWidth() const
{
	return m_width;
}

unsigned int Image::GetHeight() const
{
	return m_height;
}

void Image::Resize(unsigned int width, unsigned int height)
{
	AssertIsSizeValid(width);
	AssertIsSizeValid(height);

	m_width = width;
	m_height = height;
}