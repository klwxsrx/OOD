#include "stdafx.h"
#include "../libpainter/SvgCanvas.h"
#include "../libpainter/Shape.h"
#include "../libpainter/Rectangle.h"
#include "../libpainter/Triangle.h"
#include "../libpainter/Ellipse.h"
#include "../libpainter/RegularPolygon.h"

struct SvgCanvas_
{
	CSvgCanvas canvas;
	SvgCanvas_()
	{
		canvas.SetColor(Color::Red);
	}
};

BOOST_FIXTURE_TEST_SUITE(SvgCanvas, SvgCanvas_)
	
	BOOST_AUTO_TEST_CASE(can_draw_a_line)
	{
		canvas.DrawLine(CPoint(100, 150), CPoint(200, 250));
		BOOST_CHECK_EQUAL(canvas.GetResult(), "<?xml version=\"1.0\" encoding=\"utf - 8\"?><!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\"><svg version = \"1.1\" width = \"100%\" height = \"100%\" xmlns = \"http://www.w3.org/2000/svg\" xmlns:xlink = \"http://www.w3.org/1999/xlink\" x=\"0px\" y=\"0px\"><line x1=\"100\" y1=\"150\" x2=\"200\" y2=\"250\" style=\"stroke:rgb(255, 0, 0);stroke-width:2\"/></svg>");
	}

	BOOST_AUTO_TEST_CASE(can_draw_a_ellipse)
	{
		canvas.DrawEclipse(CPoint(100, 150), 100, 50);
		BOOST_CHECK_EQUAL(canvas.GetResult(), "<?xml version=\"1.0\" encoding=\"utf - 8\"?><!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\"><svg version = \"1.1\" width = \"100%\" height = \"100%\" xmlns = \"http://www.w3.org/2000/svg\" xmlns:xlink = \"http://www.w3.org/1999/xlink\" x=\"0px\" y=\"0px\"><ellipse cx=\"100\" cy=\"150\" rx=\"100\" ry=\"50\" style=\"fill:none; stroke:rgb(255, 0, 0); stroke - width:2\"/></svg>");
	}

	BOOST_AUTO_TEST_CASE(can_draw_mupltiple_things)
	{
		canvas.SetColor(Color::Black);
		canvas.DrawLine(CPoint(300, 140), CPoint(100, 210));

		canvas.SetColor(Color::Blue);
		canvas.DrawEclipse(CPoint(250, 300), 75, 40);

		canvas.SetColor(Color::Green);
		canvas.DrawLine(CPoint(100, 140), CPoint(170, 280));

		canvas.SetColor(Color::Pink);
		canvas.DrawEclipse(CPoint(75, 56), 31, 81);

		canvas.SetColor(Color::Red);
		canvas.DrawEclipse(CPoint(180, 350), 12, 146);

		canvas.SetColor(Color::Yellow);
		canvas.DrawEclipse(CPoint(210, 57), 34, 81);

		std::string result = canvas.GetResult();
		BOOST_CHECK_EQUAL(canvas.GetResult(), "<?xml version=\"1.0\" encoding=\"utf - 8\"?><!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\"><svg version = \"1.1\" width = \"100%\" height = \"100%\" xmlns = \"http://www.w3.org/2000/svg\" xmlns:xlink = \"http://www.w3.org/1999/xlink\" x=\"0px\" y=\"0px\"><line x1=\"300\" y1=\"140\" x2=\"100\" y2=\"210\" style=\"stroke:rgb(0, 0, 0);stroke-width:2\"/><ellipse cx=\"250\" cy=\"300\" rx=\"75\" ry=\"40\" style=\"fill:none; stroke:rgb(0, 0, 255); stroke - width:2\"/><line x1=\"100\" y1=\"140\" x2=\"170\" y2=\"280\" style=\"stroke:rgb(0, 255, 0);stroke-width:2\"/><ellipse cx=\"75\" cy=\"56\" rx=\"31\" ry=\"81\" style=\"fill:none; stroke:rgb(255, 203, 219); stroke - width:2\"/><ellipse cx=\"180\" cy=\"350\" rx=\"12\" ry=\"146\" style=\"fill:none; stroke:rgb(255, 0, 0); stroke - width:2\"/><ellipse cx=\"210\" cy=\"57\" rx=\"34\" ry=\"81\" style=\"fill:none; stroke:rgb(255, 255, 0); stroke - width:2\"/></svg>");
	}

BOOST_AUTO_TEST_SUITE_END()