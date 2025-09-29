#ifndef COLOR_H
#define COLOR_H
#include <cstdint>
#include <iostream>

class Color
{
public:
	Color(uint8_t red, uint8_t green, uint8_t blue);
	static Color FromString(const std::string& hex);
	std::string ToString() const;

private:
	uint8_t m_red;
	uint8_t m_green;
	uint8_t m_blue;
};

#endif // COLOR_H