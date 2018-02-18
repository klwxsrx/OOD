#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <string>
#include <map>
#include "Observer.h"

using namespace std;

struct SWeatherInfo
{
	std::string location;
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
};

class CDisplay: public IObserver<SWeatherInfo>
{
private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
		Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
		остается публичным
	*/
	void Update(SWeatherInfo const& data) override
	{
		std::cout << "Location: " << data.location << std::endl;
		std::cout << "Current Temp " << data.temperature << std::endl;
		std::cout << "Current Hum " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;
		std::cout << std::endl << std::endl << std::endl;
	}
};

class CParameterStatsAccumulator
{
public:
	void Add(double value)
	{
		if (m_minValue > value)
		{
			m_minValue = value;
		}
		if (m_maxValue < value)
		{
			m_maxValue = value;
		}
		m_accValue += value;
		++m_countAcc;
	}

	double GetMinValue() const
	{
		return m_minValue;
	}
	double GetMaxValue() const
	{
		return m_maxValue;
	}
	double GetAverageValue() const
	{
		return (m_countAcc != 0) ? (m_accValue / m_countAcc) : 0;
	}

private:
	double m_minValue = std::numeric_limits<double>::infinity();
	double m_maxValue = -std::numeric_limits<double>::infinity();
	double m_accValue = 0;
	unsigned m_countAcc = 0;
};

struct AccumulatedWeatherStats
{
	CParameterStatsAccumulator temperatureAccumulator;
	CParameterStatsAccumulator humidityAccumulator;
	CParameterStatsAccumulator pressureAccumulator;
};

class CStatsDisplay : public IObserver<SWeatherInfo>
{
private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
	Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
	остается публичным
	*/
	void Update(SWeatherInfo const& data) override
	{
		auto stats = GetOrCreateStats(data.location);
		UpdateStats(stats, data);
		PrintStats(stats, data.location);
	}

	AccumulatedWeatherStats* GetOrCreateStats(std::string locationName)
	{
		auto pos = m_weatherStats.find(locationName);
		if (pos == m_weatherStats.end()) {
			auto result = m_weatherStats.emplace(locationName, AccumulatedWeatherStats());
			if (result.second == false)
			{
				throw runtime_error("Can't create weather stats!");
			}
			else
			{
				pos = result.first;
			}
		}
		return &pos->second;
	}

	void UpdateStats(AccumulatedWeatherStats * stats, SWeatherInfo const& data)
	{
		stats->temperatureAccumulator.Add(data.temperature);
		stats->humidityAccumulator.Add(data.humidity);
		stats->pressureAccumulator.Add(data.pressure);
	}

	void PrintStats(AccumulatedWeatherStats const* stats, std::string const& location) const
	{
		std::cout << "Location: " << location << std::endl;
		PrintParameterStats("Temp", stats->temperatureAccumulator);
		PrintParameterStats("Hum", stats->humidityAccumulator);
		PrintParameterStats("Pressure", stats->pressureAccumulator);
		std::cout << std::endl << std::endl << std::endl;
	}

	void PrintParameterStats(std::string const& parameterName, CParameterStatsAccumulator const& statsAccumulator) const
	{
		std::cout << "-" << std::endl;
		std::cout << "Max " << parameterName << " " << statsAccumulator.GetMaxValue() << std::endl;
		std::cout << "Min " << parameterName << " " << statsAccumulator.GetMinValue() << std::endl;
		std::cout << "Average " << parameterName << " " << statsAccumulator.GetAverageValue() << std::endl;
	}

	std::map<std::string, AccumulatedWeatherStats> m_weatherStats;
};

class CWeatherData : public CObservable<SWeatherInfo>
{
public:

	CWeatherData(std::string const& name)
		: m_name(name)
	{}

	// Температура в градусах Цельсия
	double GetTemperature()const
	{
		return m_temperature;
	}
	// Относительная влажность (0...100)
	double GetHumidity()const
	{
		return m_humidity;
	}
	// Атмосферное давление (в мм.рт.ст)
	double GetPressure()const
	{
		return m_pressure;
	}

	void MeasurementsChanged()
	{
		NotifyObservers();
	}

	void SetMeasurements(double temp, double humidity, double pressure)
	{
		m_humidity = humidity;
		m_temperature = temp;
		m_pressure = pressure;

		MeasurementsChanged();
	}
protected:
	SWeatherInfo GetChangedData()const override
	{
		SWeatherInfo info;
		info.location = m_name;
		info.temperature = GetTemperature();
		info.humidity = GetHumidity();
		info.pressure = GetPressure();
		return info;
	}
private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;	
	double m_pressure = 760.0;

	std::string m_name;
};
