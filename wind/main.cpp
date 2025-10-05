#include <Displays.h>

int main()
{
	try
	{
		CWeatherDataPro proStation("Pro Station");
		auto proDisplay = std::make_shared<CProStatsDisplay>();

		proStation.RegisterObserver(proDisplay);

		proStation.SetMeasurements(20.0, 60.0, 760.0, 5.0, 350.0);
		proStation.SetMeasurements(21.0, 62.0, 761.0, 6.0, 10.0);
	}
	catch (std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
