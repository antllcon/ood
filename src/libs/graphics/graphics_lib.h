#pragma once
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <ostream>

namespace graphics_lib
{
class ICanvas
{
public:
	virtual ~ICanvas() = default;
	virtual void SetColor(uint32_t rgbColor) = 0;
	virtual void MoveTo(int x, int y) = 0;
	virtual void LineTo(int x, int y) = 0;
};

class Canvas final : public ICanvas
{
public:
	void SetColor(uint32_t rgbColor) override
	{
		std::cout << "SetColor (#"
				  << std::hex << std::uppercase << std::setw(6) << std::setfill('0')
				  << rgbColor << ")" << std::endl;
		std::cout << std::dec << std::nouppercase;
	}

	void MoveTo(int x, int y) override
	{
		std::cout << "MoveTo (" << x << ", " << y << ")" << std::endl;
	}

	void LineTo(int x, int y) override
	{
		std::cout << "LineTo (" << x << ", " << y << ")" << std::endl;
	}
};
} // namespace graphics_lib