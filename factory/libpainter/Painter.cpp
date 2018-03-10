#include "stdafx.h"
#include "Painter.h"

void CPainter::DrawPicture(IPictureDraft const& draft, ICanvas& canvas)
{
	if (draft.IsEmpty())
	{
		return;
	}

	std::for_each(draft.begin(), draft.end(), [&](IShape const& shape) {
		shape.Draw(canvas);
	});
}