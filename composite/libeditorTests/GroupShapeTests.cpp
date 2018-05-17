#include "stdafx.h"
#include "../libEditor/GroupShape.h"
#include "../libEditor/Rectangle.h"
#include "../libEditor/Triangle.h"
#include "../libEditor/Ellipse.h"

class CTestCanvas : public ICanvas
{
public:
	struct LineD
	{
		PointD start, end;
		RGBAColor lineColor;
		double lineWidth;
		RGBAColor fillColor;
	};

	bool IsEmpty() const
	{
		return m_lines.empty();
	}

	bool DoesLineExists(PointD start, PointD end, RGBAColor lineColor = Color::BLACK_COLOR, double lineWidth = 2, RGBAColor fillColor = Color::TRANSPARENT_COLOR)
	{
		for (LineD const& line : m_lines)
		{
			if (line.start == start
				&& line.end == end
				&& line.lineColor == lineColor
				&& line.lineWidth == lineWidth
				&& line.fillColor == fillColor)
			{
				return true;
			}
		}
		return false;
	}

	void SetLineColor(RGBAColor color) override
	{
		m_lineColor = color;
	}

	void SetLineWidth(double width) override
	{
		m_lineWidth = width;
	}

	void BeginFill(RGBAColor color) override
	{
		m_fillColor = color;
		m_fillStarted = true;
	}

	void EndFill() override
	{
		m_fillStarted = false;
	}

	void MoveTo(PointD const& point) override
	{
		m_currentPoint = point;
	}

	void LineTo(PointD const& point) override
	{
		m_lines.push_back({ m_currentPoint, point, m_lineColor, m_lineWidth, m_fillColor });
		MoveTo(point);
	}

	void DrawEllipse(PointD const& center, double horizontalRadius, double verticalRadius) override
	{
	}

	RGBAColor m_lineColor;
	double m_lineWidth;
	RGBAColor m_fillColor;
	bool m_fillStarted = false;
	std::vector<LineD> m_lines;
	PointD m_currentPoint;
};

struct GroupShapeFixture
{
	std::shared_ptr<CGroupShape> shape;
	std::shared_ptr<CRectangle> rectangle;
	std::shared_ptr<CTriangle> triangle;
	CTestCanvas canvas;
	GroupShapeFixture()
		: shape(std::make_shared<CGroupShape>())
		, rectangle(std::make_shared<CRectangle>(PointD({10, 10}), 100, 100))
		, triangle(std::make_shared<CTriangle>(PointD({20, 20}), PointD({100, 100}), PointD({150, 100})))
	{
	}

	void CheckCanvasRectangleExists()
	{
		BOOST_CHECK(canvas.DoesLineExists({ 10, 10 }, { 110, 10 }));
		BOOST_CHECK(canvas.DoesLineExists({ 110, 10 }, { 110, 110 }));
		BOOST_CHECK(canvas.DoesLineExists({ 110, 110 }, { 10, 110 }));
		BOOST_CHECK(canvas.DoesLineExists({ 10, 110 }, { 10, 10 }));
	}

	void CheckCanvasTriangleExists()
	{
		BOOST_CHECK(canvas.DoesLineExists({ 20, 20 }, { 100, 100 }));
		BOOST_CHECK(canvas.DoesLineExists({ 100, 100 }, { 150, 100 }));
		BOOST_CHECK(canvas.DoesLineExists({ 150, 100 }, { 20, 20 }));
	}
};

struct InsertedShapesFixture : public GroupShapeFixture
{
	InsertedShapesFixture()
	{
		shape->InsertShape(rectangle);
		shape->InsertShape(triangle);
	}
};

BOOST_FIXTURE_TEST_SUITE(GroupShape, GroupShapeFixture)
	
	BOOST_AUTO_TEST_SUITE(when_empty)
		
		BOOST_AUTO_TEST_CASE(draw_nothing)
		{
			shape->Draw(canvas);
			BOOST_CHECK(canvas.IsEmpty());
		}

		BOOST_AUTO_TEST_CASE(returns_zero_frame)
		{
			auto frame = shape->GetFrame();
			BOOST_CHECK_EQUAL(frame.height, 0);
			BOOST_CHECK_EQUAL(frame.leftTop.x, 0);
			BOOST_CHECK_EQUAL(frame.leftTop.y, 0);
			BOOST_CHECK_EQUAL(frame.width, 0);

			shape->SetFrame({ { 100, 100 }, 100, 100 });
			BOOST_CHECK_EQUAL(frame.height, 0);
			BOOST_CHECK_EQUAL(frame.leftTop.x, 0);
			BOOST_CHECK_EQUAL(frame.leftTop.y, 0);
			BOOST_CHECK_EQUAL(frame.width, 0);
		}

		BOOST_AUTO_TEST_CASE(returns_null_outline_style)
		{
			IOutlineStyle& style = shape->GetOutlineStyle();
			BOOST_CHECK(!style.GetColor());
			BOOST_CHECK(!style.GetStrokeWidth());
			BOOST_CHECK(!style.IsEnabled().is_initialized());
		}

		BOOST_AUTO_TEST_CASE(returns_null_fill_style)
		{
			IStyle& style = shape->GetFillStyle();
			BOOST_CHECK(!style.GetColor());
			BOOST_CHECK(!style.IsEnabled().is_initialized());
		}

		BOOST_AUTO_TEST_CASE(returns_itself_when_get_group)
		{
			BOOST_CHECK(shape->GetGroup() == shape);
		}

		BOOST_AUTO_TEST_CASE(returns_error_when_inserts_itself)
		{
			BOOST_CHECK_THROW(shape->InsertShape(shape), std::runtime_error);
		}

		BOOST_AUTO_TEST_CASE(returns_error_when_inserts_at_wrong_position)
		{
			BOOST_CHECK_THROW(shape->InsertShape(shape, 1), std::runtime_error);
		}

		BOOST_AUTO_TEST_CASE(inserts_shape_at_back)
		{
			BOOST_CHECK_NO_THROW(shape->InsertShape(rectangle));
			shape->Draw(canvas);
			CheckCanvasRectangleExists();
		}

		BOOST_AUTO_TEST_CASE(inserts_shape_by_index)
		{
			BOOST_CHECK_NO_THROW(shape->InsertShape(rectangle, 0));
			shape->Draw(canvas);
			CheckCanvasRectangleExists();
			BOOST_CHECK_EQUAL(canvas.m_lines.size(), 4);
		}

		BOOST_AUTO_TEST_CASE(returns_error_when_trying_to_get_shape)
		{
			BOOST_CHECK_THROW(shape->GetShapeAtIndex(0), std::runtime_error);
			BOOST_CHECK_THROW(shape->GetShapeAtIndex(1), std::runtime_error);
		}

		BOOST_AUTO_TEST_CASE(returns_error_when_trying_to_delete_shape)
		{
			BOOST_CHECK_THROW(shape->RemoveShapeAtIndex(0), std::runtime_error);
			BOOST_CHECK_THROW(shape->RemoveShapeAtIndex(1), std::runtime_error);
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_FIXTURE_TEST_SUITE(when_inserted_some_shapes, InsertedShapesFixture)
	
		BOOST_AUTO_TEST_CASE(can_draw_shapes_to_canvas)
		{
			shape->Draw(canvas);
			CheckCanvasRectangleExists();
			CheckCanvasTriangleExists();
			BOOST_CHECK_EQUAL(canvas.m_lines.size(), 7);
		}

		BOOST_AUTO_TEST_CASE(returns_shapes_frame)
		{
			auto frame = shape->GetFrame();
			BOOST_CHECK(frame.height == 100);
			BOOST_CHECK(frame.width == 140);
			BOOST_CHECK(frame.leftTop.x == 10);
			BOOST_CHECK(frame.leftTop.y == 10);
		}

		BOOST_AUTO_TEST_CASE(can_set_frame)
		{
			shape->SetFrame({ { 0, 5 }, 400, 500 });
			auto frame = shape->GetFrame();
			BOOST_CHECK_EQUAL(frame.height, 500);
			BOOST_CHECK_EQUAL(frame.width, 400);
			BOOST_CHECK_EQUAL(frame.leftTop.x, 0);
			BOOST_CHECK_EQUAL(frame.leftTop.y, 5);

			shape->Draw(canvas);
			BOOST_CHECK_EQUAL(canvas.m_lines.size(), 7);
			BOOST_CHECK(canvas.DoesLineExists({ 0, 5 }, { 285.71428571428572, 5 }));
			BOOST_CHECK(canvas.DoesLineExists({ 285.71428571428572, 5 }, { 285.71428571428572, 505 }));
			BOOST_CHECK(canvas.DoesLineExists({ 285.71428571428572, 505 }, { 0, 505 }));
			BOOST_CHECK(canvas.DoesLineExists({ 0, 505 }, { 0, 5 }));
			BOOST_CHECK(canvas.DoesLineExists({ 28.571428571428573, 55 }, { 257.14285714285717, 455 }));
			BOOST_CHECK(canvas.DoesLineExists({ 257.14285714285717, 455 }, { 400, 455 }));
			BOOST_CHECK(canvas.DoesLineExists({ 400, 455 }, { 28.571428571428573, 55 }));
		}

		BOOST_AUTO_TEST_CASE(returns_outline_style_when_all_shapes_have_the_same_style)
		{
			IOutlineStyle& style = shape->GetOutlineStyle();

			BOOST_CHECK(style.GetColor().is_initialized());
			BOOST_CHECK_EQUAL(style.GetColor().value(), Color::BLACK_COLOR);

			BOOST_CHECK(style.GetStrokeWidth().is_initialized());
			BOOST_CHECK_EQUAL(style.GetStrokeWidth().value(), 2);

			BOOST_CHECK(style.IsEnabled().is_initialized());
			BOOST_CHECK(style.IsEnabled().value());
		}

		BOOST_AUTO_TEST_CASE(returns_fill_style_when_all_shapes_have_the_same_style)
		{
			IStyle& style = shape->GetFillStyle();

			BOOST_CHECK(style.GetColor().is_initialized());
			BOOST_CHECK_EQUAL(style.GetColor().value(), Color::TRANSPARENT_COLOR);

			BOOST_CHECK(style.IsEnabled().is_initialized());
			BOOST_CHECK(!style.IsEnabled().value());
		}

		BOOST_AUTO_TEST_CASE(returns_null_when_shapes_have_different_outline_styles)
		{
			IOutlineStyle& style = shape->GetOutlineStyle();

			rectangle->GetOutlineStyle().SetColor(0xAABBCCFF);
			BOOST_CHECK(!style.GetColor().is_initialized());
			BOOST_CHECK(style.GetStrokeWidth().is_initialized());
			BOOST_CHECK(style.IsEnabled().is_initialized());

			rectangle->GetOutlineStyle().SetStrokeWidth(3);
			BOOST_CHECK(!style.GetColor().is_initialized());
			BOOST_CHECK(!style.GetStrokeWidth().is_initialized());
			BOOST_CHECK(style.IsEnabled().is_initialized());

			rectangle->GetOutlineStyle().Enable(false);
			BOOST_CHECK(!style.GetColor().is_initialized());
			BOOST_CHECK(!style.GetStrokeWidth().is_initialized());
			BOOST_CHECK(!style.IsEnabled().is_initialized());
		}

		BOOST_AUTO_TEST_CASE(returns_null_when_shapes_have_different_fill_styles)
		{
			IStyle& style = shape->GetFillStyle();

			rectangle->GetFillStyle().SetColor(0xAABBCCFF);
			BOOST_CHECK(!style.GetColor().is_initialized());
			BOOST_CHECK(style.IsEnabled().is_initialized());

			rectangle->GetFillStyle().Enable(true);
			BOOST_CHECK(!style.GetColor().is_initialized());
			BOOST_CHECK(!style.IsEnabled().is_initialized());
		}

		BOOST_AUTO_TEST_CASE(can_set_outline_style_to_shapes)
		{
			IOutlineStyle& style = shape->GetOutlineStyle();

			style.SetColor(0xAABBCCDD);
			BOOST_CHECK_EQUAL(shape->GetShapeAtIndex(0)->GetOutlineStyle().GetColor().value(), 0xAABBCCDD);
			BOOST_CHECK_EQUAL(shape->GetShapeAtIndex(1)->GetOutlineStyle().GetColor().value(), 0xAABBCCDD);

			style.SetStrokeWidth(5);
			BOOST_CHECK_EQUAL(shape->GetShapeAtIndex(0)->GetOutlineStyle().GetStrokeWidth().value(), 5);
			BOOST_CHECK_EQUAL(shape->GetShapeAtIndex(1)->GetOutlineStyle().GetStrokeWidth().value(), 5);

			style.Enable(false);
			BOOST_CHECK_EQUAL(shape->GetShapeAtIndex(0)->GetOutlineStyle().IsEnabled().value(), false);
			BOOST_CHECK_EQUAL(shape->GetShapeAtIndex(1)->GetOutlineStyle().IsEnabled().value(), false);
		}

		BOOST_AUTO_TEST_CASE(can_set_fill_style_to_shapes)
		{
			IStyle& style = shape->GetFillStyle();

			style.SetColor(0xAABBCCDD);
			BOOST_CHECK_EQUAL(shape->GetShapeAtIndex(0)->GetFillStyle().GetColor().value(), 0xAABBCCDD);
			BOOST_CHECK_EQUAL(shape->GetShapeAtIndex(1)->GetFillStyle().GetColor().value(), 0xAABBCCDD);

			style.Enable(false);
			BOOST_CHECK_EQUAL(shape->GetShapeAtIndex(0)->GetFillStyle().IsEnabled().value(), false);
			BOOST_CHECK_EQUAL(shape->GetShapeAtIndex(1)->GetFillStyle().IsEnabled().value(), false);
		}

		BOOST_AUTO_TEST_CASE(returns_shapes_count)
		{
			BOOST_CHECK_EQUAL(shape->GetShapesCount(), 2);
			shape->RemoveShapeAtIndex(0);
			BOOST_CHECK_EQUAL(shape->GetShapesCount(), 1);
			shape->InsertShape(rectangle);
			BOOST_CHECK_EQUAL(shape->GetShapesCount(), 2);
		}

		BOOST_AUTO_TEST_CASE(can_insert_shape_at_back)
		{
			shape->InsertShape(std::make_shared<CRectangle>(PointD({ 200, 300 }), 150, 250));
			BOOST_CHECK_EQUAL(shape->GetShapesCount(), 3);
			std::shared_ptr<IShape> rect = shape->GetShapeAtIndex(2);
			BOOST_CHECK_EQUAL(rect->GetFrame().leftTop.x, 200);
			BOOST_CHECK_EQUAL(rect->GetFrame().leftTop.y, 300);
			BOOST_CHECK_EQUAL(rect->GetFrame().width, 150);
			BOOST_CHECK_EQUAL(rect->GetFrame().height, 250);
		}

		BOOST_AUTO_TEST_CASE(can_insert_image_by_index_in_begin)
		{
			shape->InsertShape(std::make_shared<CRectangle>(PointD({ 200, 300 }), 150, 250), 0);
			BOOST_CHECK_EQUAL(shape->GetShapesCount(), 3);
			std::shared_ptr<IShape> rect = shape->GetShapeAtIndex(0);
			BOOST_CHECK_EQUAL(rect->GetFrame().leftTop.x, 200);
			BOOST_CHECK_EQUAL(rect->GetFrame().leftTop.y, 300);
			BOOST_CHECK_EQUAL(rect->GetFrame().width, 150);
			BOOST_CHECK_EQUAL(rect->GetFrame().height, 250);
		}

		BOOST_AUTO_TEST_CASE(can_insert_image_by_index_in_center)
		{
			shape->InsertShape(std::make_shared<CRectangle>(PointD({ 200, 300 }), 150, 250), 1);
			BOOST_CHECK_EQUAL(shape->GetShapesCount(), 3);
			std::shared_ptr<IShape> rect = shape->GetShapeAtIndex(1);
			BOOST_CHECK_EQUAL(rect->GetFrame().leftTop.x, 200);
			BOOST_CHECK_EQUAL(rect->GetFrame().leftTop.y, 300);
			BOOST_CHECK_EQUAL(rect->GetFrame().width, 150);
			BOOST_CHECK_EQUAL(rect->GetFrame().height, 250);
		}

		BOOST_AUTO_TEST_CASE(can_insert_image_by_index_at_back)
		{
			shape->InsertShape(std::make_shared<CRectangle>(PointD({ 200, 300 }), 150, 250), 2);
			BOOST_CHECK_EQUAL(shape->GetShapesCount(), 3);
			std::shared_ptr<IShape> rect = shape->GetShapeAtIndex(2);
			BOOST_CHECK_EQUAL(rect->GetFrame().leftTop.x, 200);
			BOOST_CHECK_EQUAL(rect->GetFrame().leftTop.y, 300);
			BOOST_CHECK_EQUAL(rect->GetFrame().width, 150);
			BOOST_CHECK_EQUAL(rect->GetFrame().height, 250);
		}

		BOOST_AUTO_TEST_CASE(returns_error_when_trying_to_insert_at_wrong_position)
		{
			BOOST_CHECK_THROW(shape->InsertShape(rectangle, 3), std::runtime_error);
			BOOST_CHECK_THROW(shape->InsertShape(rectangle, 4), std::runtime_error);
			BOOST_CHECK_EQUAL(shape->GetShapesCount(), 2);
		}

		BOOST_AUTO_TEST_CASE(returns_shape_by_index)
		{
			auto rect = shape->GetShapeAtIndex(0);
			BOOST_CHECK_EQUAL(rect->GetFrame().leftTop.x, 10);
			BOOST_CHECK_EQUAL(rect->GetFrame().leftTop.y, 10);
			BOOST_CHECK_EQUAL(rect->GetFrame().width, 100);
			BOOST_CHECK_EQUAL(rect->GetFrame().height, 100);

			auto triangle = shape->GetShapeAtIndex(1);
			BOOST_CHECK_EQUAL(triangle->GetFrame().leftTop.x, 20);
			BOOST_CHECK_EQUAL(triangle->GetFrame().leftTop.y, 20);
			BOOST_CHECK_EQUAL(triangle->GetFrame().width, 130);
			BOOST_CHECK_EQUAL(triangle->GetFrame().height, 80);
		}

		BOOST_AUTO_TEST_CASE(returns_error_when_trying_to_get_shape_by_wrong_index)
		{
			BOOST_CHECK_THROW(shape->GetShapeAtIndex(2), std::runtime_error);
			BOOST_CHECK_THROW(shape->GetShapeAtIndex(3), std::runtime_error);
		}

		BOOST_AUTO_TEST_CASE(removes_shape_at_index)
		{
			shape->RemoveShapeAtIndex(1);

			BOOST_CHECK_EQUAL(shape->GetShapesCount(), 1);
			auto rect = shape->GetGroup()->GetShapeAtIndex(0);
			BOOST_CHECK_EQUAL(rect->GetFrame().leftTop.x, 10);
			BOOST_CHECK_EQUAL(rect->GetFrame().leftTop.y, 10);
			BOOST_CHECK_EQUAL(rect->GetFrame().width, 100);
			BOOST_CHECK_EQUAL(rect->GetFrame().height, 100);

			shape->GetGroup()->RemoveShapeAtIndex(0);
			BOOST_CHECK_EQUAL(shape->GetShapesCount(), 0);
		}

		BOOST_AUTO_TEST_CASE(returns_error_when_trying_to_delete_shape_by_wrong_index)
		{
			BOOST_CHECK_THROW(shape->GetShapeAtIndex(2), std::runtime_error);
			BOOST_CHECK_THROW(shape->RemoveShapeAtIndex(3), std::runtime_error);
			BOOST_CHECK_EQUAL(shape->GetShapesCount(), 2);
		}

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()