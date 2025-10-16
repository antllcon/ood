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
	Black
};

inline static const std::map<std::string, Color> colorMap = {
	{"red", Color::Red},
	{"green", Color::Green},
	{"blue", Color::Blue},
	{"yellow", Color::Yellow},
	{"pink", Color::Pink},
	{"black", Color::Black}};

struct Point
{
	int x = 0;
	int y = 0;
};
