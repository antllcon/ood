#include "Color.h"
#include <iomanip>

namespace
{
constexpr size_t SHORT_FORM_HEX_SIZE = 3;
constexpr size_t USUAL_FORM_HEX_SIZE = 6;

void AssertIsHexFolmatValid(const std::string& hex)
{
	if (hex.empty() || hex[0] != '#' || (hex.length() != USUAL_FORM_HEX_SIZE + 1 && hex[0] != SHORT_FORM_HEX_SIZE + 1))
	{
		throw std::invalid_argument("Invalid hex color format");
	}
}

void AssertIsCharactersValid(const std::string& hex)
{
	for (char symbol : hex)
	{
		if (!std::isxdigit(symbol))
		{
			throw std::invalid_argument("Invalid hex characters");
		}
	}
}

void AssertIsHexValid(const std::string& hex)
{
	AssertIsHexFolmatValid(hex);
	AssertIsCharactersValid(hex);
}
} // namespace

Color::Color(const uint8_t red, const uint8_t green, const uint8_t blue)
	: m_red(red)
	, m_green(green)
	, m_blue(blue)
{
}

Color Color::FromString(const std::string& hex)
{
	AssertIsHexValid(hex);
	std::string hexValue = hex.substr(1);

	if (hexValue.length() == SHORT_FORM_HEX_SIZE)
	{
		hexValue = std::string(1, hexValue[0]) + hexValue[0]
			+ std::string(1, hexValue[1]) + hexValue[1]
			+ std::string(1, hexValue[2]) + hexValue[2];
	}

	uint8_t red;
	uint8_t green;
	uint8_t blue;
	std::stringstream stream;

	stream << std::hex << hexValue.substr(0, 2);
	stream >> red;

	stream << std::hex << hexValue.substr(2, 4);
	stream >> green;

	stream << std::hex << hexValue.substr(4, 6);
	stream >> blue;

	return Color(red, green, blue);
}

std::string Color::ToString() const
{
	std::stringstream hexStream;
	hexStream << '#'
			  << std::setw(2) << std::setfill('0') << static_cast<int>(m_red)
			  << std::setw(2) << std::setfill('0') << static_cast<int>(m_green)
			  << std::setw(2) << std::setfill('0') << static_cast<int>(m_blue);

	return hexStream.str();
}
