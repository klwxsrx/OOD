#include <stdio.h>
#include <tchar.h>
#include <memory>

#define BOOST_TEST_INCLUDED
#pragma warning (disable:4702)
#include <boost/test/unit_test.hpp>

#define BOOST_TEST_NO_MAIN

#define BOOST_TEST_DETECT_MEMORY_LEAK 1

#include <boost/test/included/unit_test.hpp>

#include <boost/test/output/compiler_log_formatter.hpp>
#include <boost/algorithm/string/replace.hpp>

#include "../observer/WeatherData.h"

using namespace std;

class CTestObserver : public IObserver<SWeatherInfo>
{
public:
	CTestObserver(std::function<void(SWeatherInfo const&)>&& callback)
		: m_callback(callback)
	{
	}

	void Update(SWeatherInfo const& data) override
	{
		m_callback(data);
	}

private:
	std::function<void(SWeatherInfo const&)> m_callback;
};

struct WeatherDataFixture
{
	const std::string weatherDataName = "test";

	shared_ptr<CWeatherData> weatherData;
	WeatherDataFixture()
	{
		weatherData = make_shared<CWeatherData>(weatherDataName);
	}
};

BOOST_FIXTURE_TEST_SUITE(WeatherData, WeatherDataFixture)

	BOOST_AUTO_TEST_CASE(shows_correct_weather_info)
	{
		BOOST_CHECK_EQUAL(weatherData->GetTemperature(), 0.0);
		BOOST_CHECK_EQUAL(weatherData->GetHumidity(), 0.0);
		BOOST_CHECK_EQUAL(weatherData->GetPressure(), 760.0);

		weatherData->SetMeasurements(3, 0.7, 761);
		BOOST_CHECK_EQUAL(weatherData->GetTemperature(), 3.0);
		BOOST_CHECK_EQUAL(weatherData->GetHumidity(), 0.7);
		BOOST_CHECK_EQUAL(weatherData->GetPressure(), 761.0);
	}

	BOOST_AUTO_TEST_CASE(shows_correct_weather_info_from_notification)
	{
		auto testObserver = make_shared<CTestObserver>([&](SWeatherInfo const&) {
			BOOST_CHECK_EQUAL(weatherData->GetTemperature(), 3.0);
			BOOST_CHECK_EQUAL(weatherData->GetHumidity(), 0.7);
			BOOST_CHECK_EQUAL(weatherData->GetPressure(), 761.0);
		});
		weatherData->RegisterObserver(testObserver.get());
		weatherData->SetMeasurements(3, 0.7, 761);
	}

	BOOST_AUTO_TEST_CASE(can_send_its_name_to_observer_in_notification)
	{
		auto testObserver = make_shared<CTestObserver>([&](SWeatherInfo const& data) {
			BOOST_CHECK_EQUAL(data.location, weatherDataName);
		});
		weatherData->RegisterObserver(testObserver.get());
		weatherData->MeasurementsChanged();
	}

	BOOST_AUTO_TEST_CASE(can_register_observer)
	{
		bool isUpdated = false;
		auto testObserver = make_shared<CTestObserver>([&](SWeatherInfo const&) {
			isUpdated = true;
		});
		weatherData->RegisterObserver(testObserver.get());
		weatherData->MeasurementsChanged();
		BOOST_CHECK(isUpdated);
	}

	BOOST_AUTO_TEST_CASE(can_remove_observer)
	{
		bool isUpdated = false;
		auto testObserver = make_shared<CTestObserver>([&](SWeatherInfo const&) {
			isUpdated = true;
		});
		weatherData->RegisterObserver(testObserver.get());
		weatherData->RemoveObserver(testObserver.get());
		weatherData->MeasurementsChanged();
		BOOST_CHECK(!isUpdated);
	}

	BOOST_AUTO_TEST_CASE(can_delete_observer_from_observer_notification)
	{
		int updateCount = 0;
		shared_ptr<CTestObserver> testObserver = make_shared<CTestObserver>([&](SWeatherInfo const&) {
			weatherData->RemoveObserver(testObserver.get());
			++updateCount;
		});
		weatherData->RegisterObserver(testObserver.get());
		weatherData->MeasurementsChanged();
		weatherData->MeasurementsChanged();
		BOOST_CHECK_EQUAL(updateCount, 1);
	}

	BOOST_AUTO_TEST_CASE(can_update_observers_by_its_priority_order)
	{
		int updateCount = 0;
		shared_ptr<CTestObserver> testObserver1 = make_shared<CTestObserver>([&](SWeatherInfo const&) {
			BOOST_CHECK_EQUAL(++updateCount, 2);
		});
		shared_ptr<CTestObserver> testObserver2 = make_shared<CTestObserver>([&](SWeatherInfo const&) {
			BOOST_CHECK_EQUAL(++updateCount, 1);
		});
		shared_ptr<CTestObserver> testObserver3 = make_shared<CTestObserver>([&](SWeatherInfo const&) {
			BOOST_CHECK_EQUAL(++updateCount, 3);
		});

		weatherData->RegisterObserver(testObserver1.get(), 2);
		weatherData->RegisterObserver(testObserver2.get(), 3);
		weatherData->RegisterObserver(testObserver3.get(), 1);
		
		weatherData->MeasurementsChanged();
	}

BOOST_AUTO_TEST_SUITE_END()

/*
Данный класс управляет форматированием журнала запуска тестов
Для того, чтобы увидеть результат, приложение должно быть запущено с ключём --log_level=test_suite (см. Post-build event в настройках проекта)
*/
class SpecLogFormatter :
	public boost::unit_test::output::compiler_log_formatter
{
	virtual void test_unit_start(std::ostream &os, boost::unit_test::test_unit const& tu) override
	{
		// перед запуском test unit-а выводим имя test unit-а, заменяя символ подчеркивания на пробел
		os << std::string(m_indent, ' ') << boost::replace_all_copy(tu.p_name.get(), "_", " ") << std::endl;
		// увеличиваем отступ для вывода имен последующих test unit-ов в виде дерева
		m_indent += 2;
	}

	virtual void test_unit_finish(std::ostream &/*os*/, boost::unit_test::test_unit const& /*tu*/, unsigned long /*elapsed*/) override
	{
		// по окончании test unit-а уменьшаем отступ
		m_indent -= 2;
	}

	int m_indent = 0;
};

boost::unit_test::test_suite* init_unit_test_suite(int /*argc*/, char* /*argv*/[])
{
	// Заменили имя log formatter на пользовательский
	boost::unit_test::unit_test_log.set_formatter(new SpecLogFormatter);
	// Имя корневого набора тестов - All tests
	boost::unit_test::framework::master_test_suite().p_name.value = "All tests";
	return 0;
}


int main(int argc, char* argv[])
{
	// Запускаем тесты, передавая параметры командной строки и кастомную функцию инициализации тестов
	return boost::unit_test::unit_test_main(&init_unit_test_suite, argc, argv);
}