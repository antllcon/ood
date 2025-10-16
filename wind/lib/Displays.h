#pragma once

#include "Observer.h"
#include "Statistics.h"
#include "WeatherDataTypes.h"
#include <iostream>
#include <map>

class CDisplay final : public IObserver<SWeatherInfo>
{
private:
	void Update(const SWeatherInfo& data, IObservable<SWeatherInfo>* subject) override
	{
		std::cout << "============" << std::endl;
		std::cout << "Signal from: " << data.stationName << std::endl;
		std::cout << "Temperature " << data.temperature << std::endl;
		std::cout << "Humidity " << data.humidity << std::endl;
		std::cout << "Pressure " << data.pressure << std::endl;
	}
};

class CAdvancedDisplay final : public IObserver<SWeatherInfo>
{
private:
	struct StationData
	{
		double temperature = 0;
		double humidity = 0;
		double pressure = 0;
	};

	void Update(const SWeatherInfo& data, IObservable<SWeatherInfo>* subject) override
	{
		m_dataStation[subject] = {
			data.temperature,
			data.humidity,
			data.pressure};

		std::cout << "============" << std::endl;

		for (const auto& [stationPtr, station] : m_dataStation)
		{
			std::cout << "  Temperature: " << station.temperature << std::endl;
			std::cout << "  Humidity: " << station.humidity << std::endl;
			std::cout << "  Pressure: " << station.pressure << std::endl;
		}

		std::cout << std::endl;
	}

	std::map<IObservable<SWeatherInfo>*, StationData> m_dataStation;
};

class CStatsDisplay final : public IObserver<SWeatherInfo>
{
private:
	void Update(const SWeatherInfo& data, IObservable<SWeatherInfo>* subject) override
	{
		m_temperature.Update(data.temperature);
		m_humidity.Update(data.humidity);
		m_pressure.Update(data.pressure);

		std::cout << "============" << std::endl;

		std::cout << "Temperature: " << std::endl
				  << "max = " << m_temperature.GetMax() << std::endl
				  << "min = " << m_temperature.GetMin() << std::endl
				  << "avg = " << m_temperature.GetAverage() << std::endl
				  << std::endl;

		std::cout << "Humidity: " << std::endl
				  << "max = " << m_humidity.GetMax() << std::endl
				  << "min = " << m_humidity.GetMin() << std::endl
				  << "avg = " << m_humidity.GetAverage() << std::endl
				  << std::endl;

		std::cout << "Pressure: " << std::endl
				  << "max = " << m_pressure.GetMax() << std::endl
				  << "min = " << m_pressure.GetMin() << std::endl
				  << "avg = " << m_pressure.GetAverage() << std::endl
				  << std::endl;
	}

	CStatsCounter m_temperature;
	CStatsCounter m_humidity;
	CStatsCounter m_pressure;
};

class CProStatsDisplay final : public IObserver<SWeatherInfo>
{
private:
	void Update(const SWeatherInfo& data, IObservable<SWeatherInfo>* subject) override
	{
		m_temperature.Update(data.temperature);
		m_humidity.Update(data.humidity);
		m_pressure.Update(data.pressure);
		m_windSpeed.Update(data.wind.speed);
		m_windDirection.Update(data.wind.direction);

		DisplayStats();
	}

	void DisplayStats() const
	{
		std::cout << "=======================" << std::endl;
		std::cout << "!Pro super duper stats!" << std::endl;

		std::cout << "Temperature: " << m_temperature.GetAverage()
				  << "°C (min: " << m_temperature.GetMin()
				  << ", max: " << m_temperature.GetMax() << ")" << std::endl;

		std::cout << "Wind Speed: " << m_windSpeed.GetAverage()
				  << " m/s (min: " << m_windSpeed.GetMin()
				  << ", max: " << m_windSpeed.GetMax() << ")" << std::endl;

		std::cout << "Wind Direction: " << m_windDirection.GetAverage()
				  << "° (min: " << m_windDirection.GetMin()
				  << ", max: " << m_windDirection.GetMax() << ")" << std::endl;
	}

	CStatsCounter m_temperature;
	CStatsCounter m_humidity;
	CStatsCounter m_pressure;
	CStatsCounter m_windSpeed;
	CWindDirectionCounter m_windDirection;
};
