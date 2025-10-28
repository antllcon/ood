#pragma once
#include <string>

class IImage
{
public:
	virtual ~IImage() = default;

	virtual const std::string& GetPath() const = 0;
	virtual unsigned int GetWidth() const = 0;
	virtual unsigned int GetHeight() const = 0;
	virtual void Resize(unsigned int width, unsigned int height) = 0;
};