#pragma once
#include <string>

struct SWindInfo
{
	double speed = 0;
	double direction = 0;
};

struct SWeatherInfo
{
	std::string stationName;
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
	SWindInfo wind;
};
