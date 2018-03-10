#include "stdafx.h"
#include "../libpainter/ShapeFactory.h"

using namespace std;

struct ShapeFactory_
{
	CShapeFactory factory;
};

BOOST_FIXTURE_TEST_SUITE(ShapeFactory, ShapeFactory_)

	BOOST_AUTO_TEST_CASE(throws_error_on_empty_description)
	{
		BOOST_CHECK_THROW(factory.CreateShape(""), std::runtime_error);
	}

	BOOST_AUTO_TEST_CASE(throws_error_on_unknown_shape)
	{
		BOOST_CHECK_THROW(factory.CreateShape("Unknown"), std::runtime_error);
	}

	BOOST_AUTO_TEST_CASE(can_create_rectangle)
	{
		auto shape = factory.CreateShape("Rectangle 100:150 200:250 Pink");
		CRectangle* rectPtr = nullptr;

		BOOST_CHECK_NO_THROW(rectPtr = static_cast<CRectangle*>(shape.get()));
		BOOST_CHECK(rectPtr->GetLeftTop() == CPoint(100, 150));
		BOOST_CHECK(rectPtr->GetRightBottom() == CPoint(200, 250));
		BOOST_CHECK(rectPtr->GetColor() == Color::Pink);
	}

	BOOST_AUTO_TEST_CASE(throws_error_on_wrong_rectangle_parameters)
	{
		BOOST_CHECK_THROW(factory.CreateShape("Rectangle"), std::runtime_error);
		BOOST_CHECK_THROW(factory.CreateShape("Rectangle 100:150"), std::runtime_error);
		BOOST_CHECK_THROW(factory.CreateShape("Rectangle 100:150 200:250"), std::runtime_error);

		BOOST_CHECK_THROW(factory.CreateShape("Rectangle 100 200:250 Pink"), std::runtime_error);
		BOOST_CHECK_THROW(factory.CreateShape("Rectangle 100:150 200 Pink"), std::runtime_error);
		BOOST_CHECK_THROW(factory.CreateShape("Rectangle 100:150 200:250 UnknownColor"), std::runtime_error);
	}

	BOOST_AUTO_TEST_CASE(can_create_triangle)
	{
		auto shape = factory.CreateShape("Triangle 100:150 200:250 300:350 Pink");
		CTriangle* trianglePtr = nullptr;

		BOOST_CHECK_NO_THROW(trianglePtr = static_cast<CTriangle*>(shape.get()));
		BOOST_CHECK(trianglePtr->GetVertex1() == CPoint(100, 150));
		BOOST_CHECK(trianglePtr->GetVertex2() == CPoint(200, 250));
		BOOST_CHECK(trianglePtr->GetVertex3() == CPoint(300, 350));
		BOOST_CHECK(trianglePtr->GetColor() == Color::Pink);
	}

	BOOST_AUTO_TEST_CASE(throws_error_on_wrong_triangle_parameters)
	{
		BOOST_CHECK_THROW(factory.CreateShape("Triangle"), std::runtime_error);
		BOOST_CHECK_THROW(factory.CreateShape("Triangle 100:150"), std::runtime_error);
		BOOST_CHECK_THROW(factory.CreateShape("Triangle 100:150 200:250"), std::runtime_error);
		BOOST_CHECK_THROW(factory.CreateShape("Triangle 100:150 200:250 300:350"), std::runtime_error);

		BOOST_CHECK_THROW(factory.CreateShape("Triangle 100 200:250 300:350 Pink"), std::runtime_error);
		BOOST_CHECK_THROW(factory.CreateShape("Triangle 100:150 200 300:350 Pink"), std::runtime_error);
		BOOST_CHECK_THROW(factory.CreateShape("Triangle 100:150 200:250 300 Pink"), std::runtime_error);
		BOOST_CHECK_THROW(factory.CreateShape("Triangle 100:150 200:250 300:350 UnknownColor"), std::runtime_error);
	}

	BOOST_AUTO_TEST_CASE(can_create_ellipse)
	{
		auto shape = factory.CreateShape("Ellipse 100:150 200 100 Pink");
		CEllipse* ellipsePtr = nullptr;

		BOOST_CHECK_NO_THROW(ellipsePtr = static_cast<CEllipse*>(shape.get()));
		BOOST_CHECK(ellipsePtr->GetCenter() == CPoint(100, 150));
		BOOST_CHECK(ellipsePtr->GetHorizontalRadius() == 200);
		BOOST_CHECK(ellipsePtr->GetVerticalRadius() == 100);
		BOOST_CHECK(ellipsePtr->GetColor() == Color::Pink);
	}

	BOOST_AUTO_TEST_CASE(throws_error_on_wrong_ellipse_parameters)
	{
		BOOST_CHECK_THROW(factory.CreateShape("Ellipse"), std::runtime_error);
		BOOST_CHECK_THROW(factory.CreateShape("Ellipse 100:150"), std::runtime_error);
		BOOST_CHECK_THROW(factory.CreateShape("Ellipse 100:150 200"), std::runtime_error);
		BOOST_CHECK_THROW(factory.CreateShape("Ellipse 100:150 200 100"), std::runtime_error);

		BOOST_CHECK_THROW(factory.CreateShape("Ellipse 100 200 100 Pink"), std::runtime_error);
		BOOST_CHECK_THROW(factory.CreateShape("Ellipse 100:150 test 100 Pink"), std::runtime_error);
		BOOST_CHECK_THROW(factory.CreateShape("Ellipse 100:150 200 test Pink"), std::runtime_error);
		BOOST_CHECK_THROW(factory.CreateShape("Ellipse 100:150 200 100 UnknownColor"), std::runtime_error);
	}

	BOOST_AUTO_TEST_CASE(can_create_regular_polygon)
	{
		auto shape = factory.CreateShape("RegularPolygon 100:150 200 6 Pink");
		CRegularPolygon* polygonPtr = nullptr;

		BOOST_CHECK_NO_THROW(polygonPtr = static_cast<CRegularPolygon*>(shape.get()));
		BOOST_CHECK(polygonPtr->GetCenter() == CPoint(100, 150));
		BOOST_CHECK(polygonPtr->GetRadius() == 200);
		BOOST_CHECK(polygonPtr->GetVertexCount() == 6);
		BOOST_CHECK(polygonPtr->GetColor() == Color::Pink);
	}

	BOOST_AUTO_TEST_CASE(throws_error_on_wrong_regular_polygon_parameters)
	{
		BOOST_CHECK_THROW(factory.CreateShape("RegularPolygon"), std::runtime_error);
		BOOST_CHECK_THROW(factory.CreateShape("RegularPolygon 100:150"), std::runtime_error);
		BOOST_CHECK_THROW(factory.CreateShape("RegularPolygon 100:150"), std::runtime_error);
		BOOST_CHECK_THROW(factory.CreateShape("RegularPolygon 100:150 200"), std::runtime_error);
		BOOST_CHECK_THROW(factory.CreateShape("RegularPolygon 100:150 200 6"), std::runtime_error);

		BOOST_CHECK_THROW(factory.CreateShape("RegularPolygon 100 200 Pink"), std::runtime_error);
		BOOST_CHECK_THROW(factory.CreateShape("RegularPolygon 100:150 test Pink"), std::runtime_error);
		BOOST_CHECK_THROW(factory.CreateShape("RegularPolygon 100:150 200 UnknownColor"), std::runtime_error);
	}

BOOST_AUTO_TEST_SUITE_END()