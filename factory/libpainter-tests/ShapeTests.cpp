#include "stdafx.h"
#include "TestCanvas.h"
#include "../libpainter/Shape.h"
#include "../libpainter/Rectangle.h"
#include "../libpainter/Triangle.h"
#include "../libpainter/Ellipse.h"
#include "../libpainter/RegularPolygon.h"

struct TestCanvas_
{
	CTestCanvas canvas;
};

struct Rectangle_ : TestCanvas_
{
	CRectangle rect;
	CPoint leftTop;
	CPoint leftBottom;
	CPoint rightTop;
	CPoint rightBottom;
	Color color;

	Rectangle_()
		: leftTop(100, 200)
		, leftBottom(100, 300)
		, rightTop(400, 200)
		, rightBottom(400, 300)
		, color(Color::Red)
		, rect(CPoint(100, 200), CPoint(400, 300), Color::Red)
	{
	}
};

struct Triangle_ : TestCanvas_
{
	CTriangle triangle;
	CPoint vertex1;
	CPoint vertex2;
	CPoint vertex3;
	Color color;

	Triangle_()
		: vertex1(200, 100)
		, vertex2(300, 200)
		, vertex3(100, 200)
		, color(Color::Red)
		, triangle(CPoint(200, 100), CPoint(300, 200), CPoint(100, 200), Color::Red)
	{
	}
};

struct Ellipse_ : TestCanvas_
{
	CEllipse ellipse;
	CPoint center;
	unsigned horizontalRadius, verticalRadius;
	Color color;

	Ellipse_()
		: ellipse(CPoint(200, 200), 150, 100, Color::Red)
		, center(200, 200)
		, horizontalRadius(150)
		, verticalRadius(100)
		, color(Color::Red)
	{
	}
};

struct RegularPolygon_ : TestCanvas_
{
	CPoint center;
	unsigned vertexCount, radius;
	CRegularPolygon polygon;
	Color color;

	RegularPolygon_()
		: center(200, 200)
		, vertexCount(3)
		, radius(100)
		, polygon(CPoint(200, 200), 100, 3, Color::Red)
		, color(Color::Red)
	{
	}
};

BOOST_AUTO_TEST_SUITE(Rectangle)
	
	BOOST_AUTO_TEST_CASE(can_be_created_with_correct_parameters)
	{
		BOOST_CHECK_NO_THROW(CRectangle(CPoint(2, 2), CPoint(3, 3), Color::Black));
		
		BOOST_CHECK_THROW(CRectangle(CPoint(2, 2), CPoint(2, 2), Color::Black), std::logic_error);

		BOOST_CHECK_THROW(CRectangle(CPoint(2, 2), CPoint(2, 3), Color::Black), std::logic_error);
		BOOST_CHECK_THROW(CRectangle(CPoint(2, 2), CPoint(3, 2), Color::Black), std::logic_error);

		BOOST_CHECK_THROW(CRectangle(CPoint(2, 2), CPoint(1, 3), Color::Black), std::logic_error);
		BOOST_CHECK_THROW(CRectangle(CPoint(2, 2), CPoint(3, 1), Color::Black), std::logic_error);
	}

	BOOST_FIXTURE_TEST_CASE(can_return_its_position, Rectangle_)
	{
		BOOST_CHECK(rect.GetLeftTop() == leftTop);
		BOOST_CHECK(rect.GetRightBottom() == rightBottom);
	}

	BOOST_FIXTURE_TEST_CASE(can_return_its_color, Rectangle_)
	{
		BOOST_CHECK(rect.GetColor() == color);
	}

	BOOST_FIXTURE_TEST_CASE(can_be_drawn_on_canvas, Rectangle_)
	{
		rect.Draw(canvas);
		BOOST_CHECK_EQUAL(canvas.GetEllipsesCount(), 0);
		BOOST_CHECK_EQUAL(canvas.GetLinesCount(), 4);
		BOOST_CHECK(canvas.HasLine(leftTop, rightTop));
		BOOST_CHECK(canvas.HasLine(rightTop, rightBottom));
		BOOST_CHECK(canvas.HasLine(rightBottom, leftBottom));
		BOOST_CHECK(canvas.HasLine(leftBottom, leftTop));
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Triangle)

	BOOST_AUTO_TEST_CASE(can_be_created_with_correct_parameters)
	{
		BOOST_CHECK_NO_THROW(CTriangle(CPoint(200, 100), CPoint(300, 200), CPoint(100, 200), Color::Red));

		BOOST_CHECK_THROW(CTriangle(CPoint(200, 100), CPoint(200, 100), CPoint(200, 100), Color::Red), std::logic_error);
		BOOST_CHECK_THROW(CTriangle(CPoint(200, 100), CPoint(200, 100), CPoint(100, 200), Color::Red), std::logic_error);
		BOOST_CHECK_THROW(CTriangle(CPoint(200, 100), CPoint(300, 200), CPoint(200, 100), Color::Red), std::logic_error);
		BOOST_CHECK_THROW(CTriangle(CPoint(200, 100), CPoint(300, 200), CPoint(300, 200), Color::Red), std::logic_error);
	}

	BOOST_FIXTURE_TEST_CASE(can_return_its_position, Triangle_)
	{
		BOOST_CHECK(triangle.GetVertex1() == vertex1);
		BOOST_CHECK(triangle.GetVertex2() == vertex2);
		BOOST_CHECK(triangle.GetVertex3() == vertex3);
	}

	BOOST_FIXTURE_TEST_CASE(can_return_its_color, Triangle_)
	{
		BOOST_CHECK(triangle.GetColor() == color);
	}

	BOOST_FIXTURE_TEST_CASE(can_be_drawn_on_canvas, Triangle_)
	{
		triangle.Draw(canvas);
		BOOST_CHECK_EQUAL(canvas.GetEllipsesCount(), 0);
		BOOST_CHECK_EQUAL(canvas.GetLinesCount(), 3);
		BOOST_CHECK(canvas.HasLine(vertex1, vertex2));
		BOOST_CHECK(canvas.HasLine(vertex2, vertex3));
		BOOST_CHECK(canvas.HasLine(vertex3, vertex1));
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Ellipse)

	BOOST_AUTO_TEST_CASE(can_be_created_with_correct_parameters)
	{
		BOOST_CHECK_NO_THROW(CEllipse(CPoint(200, 200), 100, 100, Color::Red));

		BOOST_CHECK_THROW(CEllipse(CPoint(200, 200), 0, 100, Color::Red), std::logic_error);
		BOOST_CHECK_THROW(CEllipse(CPoint(200, 200), 100, 0, Color::Red), std::logic_error);
	}

	BOOST_FIXTURE_TEST_CASE(can_return_its_parameters, Ellipse_)
	{
		BOOST_CHECK(ellipse.GetCenter() == center);
		BOOST_CHECK(ellipse.GetHorizontalRadius() == horizontalRadius);
		BOOST_CHECK(ellipse.GetVerticalRadius() == verticalRadius);
	}

	BOOST_FIXTURE_TEST_CASE(can_return_its_color, Ellipse_)
	{
		BOOST_CHECK(ellipse.GetColor() == color);
	}

	BOOST_FIXTURE_TEST_CASE(can_be_drawn_on_canvas, Ellipse_)
	{
		ellipse.Draw(canvas);
		BOOST_CHECK_EQUAL(canvas.GetEllipsesCount(), 1);
		BOOST_CHECK_EQUAL(canvas.GetLinesCount(), 0);
		BOOST_CHECK(canvas.HasEllipse(center, horizontalRadius, verticalRadius));
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Regular_polygon)

	BOOST_AUTO_TEST_CASE(can_be_created_with_correct_parameters)
	{
		BOOST_CHECK_NO_THROW(CRegularPolygon(CPoint(200, 200), 1, 3, Color::Red));
		BOOST_CHECK_NO_THROW(CRegularPolygon(CPoint(200, 200), 2, 4, Color::Red));

		BOOST_CHECK_THROW(CRegularPolygon(CPoint(200, 200), 0, 3, Color::Red), std::logic_error);
		BOOST_CHECK_THROW(CRegularPolygon(CPoint(200, 200), 100, 2, Color::Red), std::logic_error);
		BOOST_CHECK_THROW(CRegularPolygon(CPoint(200, 200), 100, 0, Color::Red), std::logic_error);
	}

	BOOST_FIXTURE_TEST_CASE(can_return_its_parameters, RegularPolygon_)
	{
		BOOST_CHECK(polygon.GetCenter() == center);
		BOOST_CHECK_EQUAL(polygon.GetRadius(), radius);
		BOOST_CHECK_EQUAL(polygon.GetVertexCount(), vertexCount);
	}

	BOOST_FIXTURE_TEST_CASE(can_return_its_color, RegularPolygon_)
	{
		BOOST_CHECK(polygon.GetColor() == color);
	}

	BOOST_FIXTURE_TEST_CASE(can_be_drawn_on_canvas, RegularPolygon_)
	{
		polygon.Draw(canvas);
		BOOST_CHECK_EQUAL(canvas.GetEllipsesCount(), 0);
		BOOST_CHECK_EQUAL(canvas.GetLinesCount(), vertexCount);
		
		BOOST_CHECK(canvas.HasLine(CPoint(200, 100), CPoint(282, 141)));
		BOOST_CHECK(canvas.HasLine(CPoint(282, 141), CPoint(233, 105)));
		BOOST_CHECK(canvas.HasLine(CPoint(233, 105), CPoint(200, 100)));
	}

BOOST_AUTO_TEST_SUITE_END()