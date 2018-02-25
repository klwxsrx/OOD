#include "stdafx.h"
#include "../libpainter/Shape.h"

class CMockCanvas : public ICanvas
{
public:
	void SetColor(Color color)override
	{
		canvasColor = color;
	}
	void DrawLine(CPoint const&, CPoint const&)override
	{
	}
	void DrawEclipse(CPoint const&, unsigned, unsigned)override
	{
	}

	Color canvasColor;
};

struct Shape_
{
	CShape shape;
	CMockCanvas canvas;

	Shape_()
		: shape(Color::Red)
	{
	}
};

BOOST_AUTO_TEST_SUITE(Shape)
	
	BOOST_AUTO_TEST_CASE(can_be_created_with_color)
	{
		CShape shape(Color::Black);
		BOOST_CHECK(shape.GetColor() == Color::Black);
	}

	BOOST_FIXTURE_TEST_CASE(can_set_its_color_to_canvas_when_draw, Shape_)
	{
		shape.Draw(canvas);
		BOOST_CHECK(canvas.canvasColor == Color::Red);
	}

BOOST_AUTO_TEST_SUITE_END()