#pragma once
#include <iostream>
#include <ostream>

namespace graphics_lib
{
class ICanvas
{
public:
	virtual ~ICanvas() = default;
	virtual void MoveTo(int x, int y) = 0;
	virtual void LineTo(int x, int y) = 0;
};

class Canvas final : public ICanvas
{
public:
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