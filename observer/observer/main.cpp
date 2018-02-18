#include "WeatherData.h"
#include <memory>

int main()
{
	CWeatherData weatherDataOutdoor("outdoor");
	CWeatherData weatherDataIndoor("indoor");

	auto display = make_shared<CDisplay>();
	weatherDataOutdoor.RegisterObserver(display.get());
	weatherDataIndoor.RegisterObserver(display.get());

	auto statsDisplay = make_shared<CStatsDisplay>();
	weatherDataOutdoor.RegisterObserver(statsDisplay.get());
	weatherDataIndoor.RegisterObserver(statsDisplay.get());

	weatherDataOutdoor.SetMeasurements(3, 0.7, 760);
	weatherDataOutdoor.SetMeasurements(4, 0.8, 761);
	weatherDataOutdoor.SetMeasurements(3, 0.7, 760);
	
	weatherDataIndoor.SetMeasurements(26, 0.7, 761);
	weatherDataIndoor.SetMeasurements(27, 0.8, 761);

	return 0;
}