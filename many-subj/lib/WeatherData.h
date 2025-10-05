#pragma once

#include "Observer.h"
#include <algorithm>
#include <iostream>
#include <limits>

struct SWeatherInfo
{
	std::string stationName;
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
};

class CStatsCounter final
{
public:
	void Update(double value)
	{
		if (m_min > value)
		{
			m_min = value;
		}
		if (m_max < value)
		{
			m_max = value;
		}

		m_acc += value;
		++m_count;
	}

	double GetMin() const
	{
		return m_min;
	}

	double GetMax() const
	{
		return m_max;
	}

	double GetAverage() const
	{
		if (m_count != 0)
		{
			return m_acc / m_count;
		}

		return 0;
	}

private:
	double m_min = std::numeric_limits<double>::infinity();
	double m_max = -std::numeric_limits<double>::infinity();
	double m_acc = 0;
	unsigned m_count = 0;
};

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

class CWeatherData : public CObservable<SWeatherInfo>
{
public:
	CWeatherData(const std::string& name)
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
