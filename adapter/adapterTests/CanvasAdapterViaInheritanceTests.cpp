#include "stdafx.h"
#include "../adapter/CanvasAdapterViaInheritance.h"

struct CreatedOutputStreamFixture
{
	std::ostringstream outStream;
};

struct CanvasAdapterFixture
{
	std::string TestAdapter(std::function<void(graphics_lib::ICanvas& canvas)> testFunc)
	{
		std::ostringstream outStream;
		{
			CCanvasAdapterViaInheritance adapter(outStream);
			testFunc(adapter);
		}
		return outStream.str();
	}
};

BOOST_FIXTURE_TEST_SUITE(CanvasAdapterViaInheritance, CreatedOutputStreamFixture)

	BOOST_AUTO_TEST_CASE(can_be_created)
	{
		BOOST_CHECK_NO_THROW(CCanvasAdapterViaInheritance adapter(outStream));
	}

	BOOST_FIXTURE_TEST_SUITE(created_adapter, CanvasAdapterFixture)

		BOOST_AUTO_TEST_CASE(draw_line_with_default_position_and_color)
		{
			auto result = TestAdapter([&](graphics_lib::ICanvas& canvas) {
				canvas.LineTo(100, 150);
			});
			BOOST_CHECK_EQUAL(result, R"text(<draw>
<line fromX="0" fromY="0" toX="100" toY="150"><color r="0" g="0" b="0" a="1" />
</draw>
)text");
		}

		BOOST_AUTO_TEST_CASE(draw_line_from_custom_position)
		{
			auto result = TestAdapter([&](graphics_lib::ICanvas& canvas) {
				canvas.MoveTo(10, 20);
				canvas.LineTo(100, 150);
				canvas.LineTo(200, 250);

				canvas.MoveTo(210, 250);
				canvas.LineTo(300, 350);
			});
			BOOST_CHECK_EQUAL(result, R"text(<draw>
<line fromX="10" fromY="20" toX="100" toY="150"><color r="0" g="0" b="0" a="1" />
<line fromX="100" fromY="150" toX="200" toY="250"><color r="0" g="0" b="0" a="1" />
<line fromX="210" fromY="250" toX="300" toY="350"><color r="0" g="0" b="0" a="1" />
</draw>
)text");
		}

		BOOST_AUTO_TEST_CASE(draw_line_with_custom_color)
		{
			auto result = TestAdapter([&](graphics_lib::ICanvas& canvas) {
				canvas.SetColor(0xAABBCCDD);
				canvas.LineTo(0, 0);
				canvas.LineTo(0, 0);

				canvas.SetColor(0xBBCCDDFF);
				canvas.LineTo(0, 0);
			});
			BOOST_CHECK_EQUAL(result, R"text(<draw>
<line fromX="0" fromY="0" toX="0" toY="0"><color r="0.666667" g="0.733333" b="0.8" a="0.866667" />
<line fromX="0" fromY="0" toX="0" toY="0"><color r="0.666667" g="0.733333" b="0.8" a="0.866667" />
<line fromX="0" fromY="0" toX="0" toY="0"><color r="0.733333" g="0.8" b="0.866667" a="1" />
</draw>
)text");
		}
	
	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()