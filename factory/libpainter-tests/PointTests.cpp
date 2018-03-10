#include "stdafx.h"
#include "../libpainter/Point.h"

BOOST_AUTO_TEST_SUITE(Point)
	
	BOOST_AUTO_TEST_CASE(can_be_created_with_default_values)
	{
		auto point = CPoint();
		BOOST_CHECK_EQUAL(point.x, 0);
		BOOST_CHECK_EQUAL(point.y, 0);
	}

	BOOST_AUTO_TEST_CASE(can_be_created_with_values)
	{
		auto point = CPoint(1, 2);
		BOOST_CHECK_EQUAL(point.x, 1);
		BOOST_CHECK_EQUAL(point.y, 2);
	}

	BOOST_AUTO_TEST_CASE(can_be_initalized_from_stream)
	{
		auto point = CPoint();

		std::stringstream stream("");
		BOOST_CHECK_THROW(stream >> point, std::runtime_error);

		std::stringstream stream1("12");
		BOOST_CHECK_THROW(stream1 >> point, std::runtime_error);

		std::stringstream stream2("1 2");
		BOOST_CHECK_THROW(stream2 >> point, std::runtime_error);

		std::stringstream stream3(":");
		BOOST_CHECK_THROW(stream3 >> point, std::runtime_error);

		std::stringstream stream4("1:");
		BOOST_CHECK_THROW(stream4 >> point, std::runtime_error);

		std::stringstream stream5(":2");
		BOOST_CHECK_THROW(stream5 >> point, std::runtime_error);

		std::stringstream stream6("test");
		BOOST_CHECK_THROW(stream6 >> point, std::runtime_error);

		std::stringstream stream7("test:");
		BOOST_CHECK_THROW(stream7 >> point, std::runtime_error);

		std::stringstream stream8(":test");
		BOOST_CHECK_THROW(stream8 >> point, std::runtime_error);

		std::stringstream stream9("test:test");
		BOOST_CHECK_THROW(stream9 >> point, std::runtime_error);

		std::stringstream stream10("1:2");
		BOOST_CHECK_NO_THROW(stream10 >> point);
		BOOST_CHECK_EQUAL(point.x, 1);
		BOOST_CHECK_EQUAL(point.y, 2);
	}

	BOOST_AUTO_TEST_CASE(can_be_compared)
	{
		auto point1 = CPoint(1, 2);

		auto point2 = CPoint(1, 1);
		auto point3 = CPoint(2, 2);

		BOOST_CHECK(point1 == point1);
		BOOST_CHECK(!(point1 != point1));

		BOOST_CHECK(point1 != point2);
		BOOST_CHECK(!(point1 == point2));

		BOOST_CHECK(point1 != point3);
		BOOST_CHECK(!(point1 == point3));
	}

	BOOST_AUTO_TEST_CASE(can_take_the_value_of_other_point)
	{
		auto expectedPoint = CPoint(1, 2);
		
		auto point = CPoint();
		point = expectedPoint;
		BOOST_CHECK(point == expectedPoint);
		BOOST_CHECK(point.x == 1 && point.y == 2);

		auto point1 = CPoint();
		point1 = std::move(expectedPoint);
		BOOST_CHECK(point.x == 1 && point.y == 2);
	}

BOOST_AUTO_TEST_SUITE_END()