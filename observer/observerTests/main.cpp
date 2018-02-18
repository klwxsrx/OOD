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

#include "../observer/Observer.h"

using namespace std;

class CTestObservable : public CObservable<int>
{
	int GetChangedData() const
	{
		return 0;
	}
};

struct ObserverFixture
{
	CTestObservable observable;
};

class CSelfDeleteObserver : public IObserver<int>
{
public:
	CSelfDeleteObserver(CTestObservable& observable)
		: m_observable(observable)
	{
		m_observable.RegisterObserver(this);
	}

	void Update(int const& data)
	{
		m_observable.RemoveObserver(this);
	}
private:
	CTestObservable& m_observable;
};

class CSelfAddObserver : public IObserver<int>
{
public:
	CSelfAddObserver(CTestObservable& observable)
		: m_observable(observable)
	{
		m_observable.RegisterObserver(this);
	}

	void Update(int const& data)
	{
		m_observable.RegisterObserver(this);
	}
private:
	CTestObservable& m_observable;
};

class CTestUpdatePriorityObserver : public IObserver<int>
{
public:
	CTestUpdatePriorityObserver(CTestObservable& observable, size_t priority, size_t expectedPriority, size_t& updateCounter)
		: m_expectedPriority(expectedPriority)
		, m_updateCounter(updateCounter)
	{
		observable.RegisterObserver(this, priority);
	}

	void Update(int const& data)
	{
		BOOST_CHECK_EQUAL(++m_updateCounter, m_expectedPriority);
	}
private:
	size_t m_expectedPriority;
	size_t& m_updateCounter;
};

BOOST_FIXTURE_TEST_SUITE(Observer, ObserverFixture)

	BOOST_AUTO_TEST_CASE(can_delete_observer_from_observer_notification)
	{
		auto selfDeleteObserver = make_shared<CSelfDeleteObserver>(observable);
		BOOST_CHECK_NO_THROW(observable.NotifyObservers());
	}

	BOOST_AUTO_TEST_CASE(can_register_observer_from_observer_notification)
	{
		auto selfAddObserver = make_shared<CSelfDeleteObserver>(observable);
		BOOST_CHECK_NO_THROW(observable.NotifyObservers());
	}

	BOOST_AUTO_TEST_CASE(can_update_observers_by_its_priority_order)
	{
		size_t updateCounter = 0;
		auto observer1 = make_shared<CTestUpdatePriorityObserver>(observable, 2, 2, updateCounter);
		auto observer2 = make_shared<CTestUpdatePriorityObserver>(observable, 3, 1, updateCounter);
		auto observer3 = make_shared<CTestUpdatePriorityObserver>(observable, 1, 3, updateCounter);
		observable.NotifyObservers();
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