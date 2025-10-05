#pragma once

#include "Observer.h"
#include "WeatherDataTypes.h"

#include <iostream>

class CWeatherData : public CObservable<SWeatherInfo>
{
public:
	explicit CWeatherData(const std::string& name)
		: m_stationName(name)
	{
	}

	const std::string& GetStationName() const
	{
		return m_stationName;
	}

	double GetTemperature() const
	{
		return m_temperature;
	}

	double GetHumidity() const
	{
		return m_humidity;
	}

	double GetPressure() const
	{
		return m_pressure;
	}

	void MeasurementsChanged()
	{
		NotifyObservers();
	}

	void SetMeasurements(double temp, double humidity, double pressure)
	{

		if (m_temperature != temp || m_humidity != humidity || m_pressure != pressure)
		{
			m_humidity = humidity;
			m_temperature = temp;
			m_pressure = pressure;
			MeasurementsChanged();
		}
	}

protected:
	SWeatherInfo GetChangedData() const override
	{
		SWeatherInfo info;
		info.stationName = GetStationName();
		info.temperature = GetTemperature();
		info.humidity = GetHumidity();
		info.pressure = GetPressure();

		return info;
	}

private:
	std::string m_stationName;
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
};

class CWeatherDataPro : public CObservable<SWeatherInfo>
{
public:
	CWeatherDataPro(const std::string& name)
		: m_stationName(name)
	{
	}

	void SetMeasurements(double temp, double humidity, double pressure, double windSpeed, double windDirection)
	{
		m_temperature = temp;
		m_humidity = humidity;
		m_pressure = pressure;
		m_wind.speed = windSpeed;
		m_wind.direction = windDirection;

		MeasurementsChanged();
	}

	void MeasurementsChanged()
	{
		NotifyObservers();
	}

protected:
	SWeatherInfo GetChangedData() const override
	{
		SWeatherInfo info;
		info.temperature = m_temperature;
		info.humidity = m_humidity;
		info.pressure = m_pressure;
		info.wind = m_wind;

		return info;
	}

private:
	std::string m_stationName;
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
	SWindInfo m_wind;
};
