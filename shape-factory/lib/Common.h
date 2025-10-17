#pragma once
#include <map>
#include <string>

enum class Color
{
	Red,
	Green,
	Blue,
	Yellow,
	Pink,
	Black,
	Brown,
	DarkBrown,
	Purple,
	LightBrown
};

inline static const std::map<std::string, Color> colorMap = {
	{"red", Color::Red},
	{"green", Color::Green},
	{"blue", Color::Blue},
	{"yellow", Color::Yellow},
	{"pink", Color::Pink},
	{"black", Color::Black},
	{"brown", Color::Brown},
	{"dark_brown", Color::DarkBrown},
	{"purple", Color::Purple},
	{"light_brown", Color::LightBrown},
};

struct Point
{
	int x = 0;
	int y = 0;
};
