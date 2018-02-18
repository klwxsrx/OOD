#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include "Observer.h"
#include <string>

using namespace std;

struct SWeatherInfo
{
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
		std::cout << "Current Temp " << data.temperature << std::endl;
		std::cout << "Current Hum " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;
		std::cout << "----------------" << std::endl;
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

class CStatsDisplay : public IObserver<SWeatherInfo>
{
private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
	Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
	остается публичным
	*/
	void Update(SWeatherInfo const& data) override
	{
		m_temperatureAccumulator.Add(data.temperature);
		m_humidityAccumulator.Add(data.humidity);
		m_pressureAccumulator.Add(data.pressure);

		PrintStats("Temp", m_temperatureAccumulator);
		PrintStats("Hum", m_humidityAccumulator);
		PrintStats("Pressure", m_pressureAccumulator);
	}

	void PrintStats(std::string const& parameterName, CParameterStatsAccumulator const& statsAccumulator)
	{
		std::cout << "Max " << parameterName << " " << statsAccumulator.GetMaxValue() << std::endl;
		std::cout << "Min " << parameterName << " " << statsAccumulator.GetMinValue() << std::endl;
		std::cout << "Average " << parameterName << " " << statsAccumulator.GetAverageValue() << std::endl;
		std::cout << "----------------" << std::endl;
	}

	CParameterStatsAccumulator m_temperatureAccumulator;
	CParameterStatsAccumulator m_humidityAccumulator;
	CParameterStatsAccumulator m_pressureAccumulator;
};

class CWeatherData : public CObservable<SWeatherInfo>
{
public:
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
		info.temperature = GetTemperature();
		info.humidity = GetHumidity();
		info.pressure = GetPressure();
		return info;
	}
private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;	
	double m_pressure = 760.0;
};
