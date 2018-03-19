#include "stdafx.h"
#include "../libpainter/Color.h"

struct Color_
{
	void TestColorFromStream(std::istream&& stream, Color expectedColor)
	{
		Color color;
		stream >> color;
		BOOST_CHECK(color == expectedColor);
	}

	void TestRgbColor(Color color, unsigned r, unsigned g, unsigned b)
	{
		RgbColor rgbColor(color);
		BOOST_CHECK_EQUAL(rgbColor.r, r);
		BOOST_CHECK_EQUAL(rgbColor.g, g);
		BOOST_CHECK_EQUAL(rgbColor.b, b);
	}
};

BOOST_AUTO_TEST_SUITE(ShapeColor)

	BOOST_AUTO_TEST_CASE(throws_error_when_initialized_with_wrong_color)
	{
		Color color;
		BOOST_CHECK_THROW(std::stringstream("Unknown") >> color, std::runtime_error);
	}

	BOOST_FIXTURE_TEST_CASE(can_be_initialized_from_stream, Color_)
	{
		TestColorFromStream(std::stringstream("Black"), Color::Black);
		TestColorFromStream(std::stringstream("Blue"), Color::Blue);
		TestColorFromStream(std::stringstream("Green"), Color::Green);
		TestColorFromStream(std::stringstream("Pink"), Color::Pink);
		TestColorFromStream(std::stringstream("Red"), Color::Red);
		TestColorFromStream(std::stringstream("Yellow"), Color::Yellow);
	}

	BOOST_FIXTURE_TEST_CASE(returns_correct_rgb_color, Color_)
	{
		TestRgbColor(Color::Black, 0, 0, 0);
		TestRgbColor(Color::Blue, 0, 0, 255);
		TestRgbColor(Color::Green, 0, 255, 0);
		TestRgbColor(Color::Pink, 255, 203, 219);
		TestRgbColor(Color::Red, 255, 0, 0);
		TestRgbColor(Color::Yellow, 255, 255, 0);
	}

BOOST_AUTO_TEST_SUITE_END()