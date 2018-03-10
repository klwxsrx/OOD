#include "stdafx.h"
#include "TestCanvas.h"
#include "TestShape.h"
#include "../libpainter/Painter.h"
#include "../libpainter/PictureDraft.h"
#include "../libpainter/ICanvas.h"
#include "../libpainter/IShape.h"

struct Painter_
{
	CPictureDraft draft;
	CTestCanvas canvas;
	CPainter painter;
};

struct NonEmptyDraft_ : Painter_
{
	CPoint start1, end1, center1, start2, end2, center2;
	unsigned horizontalRadius1, verticalRadius1, horizontalRadius2, verticalRadius2;

	NonEmptyDraft_()
		: start1(CPoint(100, 100)), start2(CPoint(120, 210))
		, end1(CPoint(200, 200)), end2(CPoint(340, 280))
		, center1(CPoint(150, 150)), center2(CPoint(100, 350))
		, horizontalRadius1(30), horizontalRadius2(20)
		, verticalRadius1(40), verticalRadius2(30)
	{
		draft.AddShape(std::make_unique<CTestShape>(start1, end1, center1, horizontalRadius1, verticalRadius1, Color::Blue));
		draft.AddShape(std::make_unique<CTestShape>(start2, end2, center2, horizontalRadius2, verticalRadius2, Color::Pink));
	}
};

BOOST_FIXTURE_TEST_SUITE(Painter, Painter_)
	
	BOOST_AUTO_TEST_CASE(can_draw_empty_draft_to_canvas)
	{
		painter.DrawPicture(draft, canvas);
		BOOST_CHECK(canvas.IsUntouched());
	}

	BOOST_FIXTURE_TEST_CASE(can_draw_non_empty_draft_to_canvas, NonEmptyDraft_)
	{
		painter.DrawPicture(draft, canvas);
		BOOST_CHECK(canvas.GetLinesCount() == 2);
		BOOST_CHECK(canvas.GetEllipsesCount() == 2);

		BOOST_CHECK(canvas.HasLine(start1, end1));
		BOOST_CHECK(canvas.HasLine(start2, end2));

		BOOST_CHECK(canvas.HasEllipse(center1, horizontalRadius1, verticalRadius1));
		BOOST_CHECK(canvas.HasEllipse(center2, horizontalRadius2, verticalRadius2));
	}

BOOST_AUTO_TEST_SUITE_END()