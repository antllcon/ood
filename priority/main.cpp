#include "lib/WeatherData.h"

int main()
{
	try
	{
		CWeatherData wd;
		auto statsDisplay = std::make_shared<CStatsDisplay>();

		wd.RegisterObserver(statsDisplay);

		wd.SetMeasurements(3, 0.7, 760);
		wd.SetMeasurements(4, 0.8, 761);

		wd.RemoveObserver(statsDisplay);

		wd.SetMeasurements(10, 0.8, 761);
		wd.SetMeasurements(-10, 0.8, 761);
	}
	catch (std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
