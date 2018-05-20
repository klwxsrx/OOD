#include "stdafx.h"
#include "Slide.h"

void CSlide::Draw(ICanvas& canvas) const
{
	m_shapeGroup.Draw(canvas);
}

double CSlide::GetWidth() const
{
	RectD frame = m_shapeGroup.GetFrame();
	return frame.leftTop.x + frame.width;
}

double CSlide::GetHeight() const
{
	RectD frame = m_shapeGroup.GetFrame();
	return frame.leftTop.y + frame.height;
}

IShapes& CSlide::GetShapes()
{
	return m_shapeGroup;
}
