#pragma once
#include <iostream>
#include <map>
#include <climits>

#include "WeatherData.h"

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
