#include "stdafx.h"
#include "Rectangle.h"

CRectangle::CRectangle(PointD leftTop, double width, double height)
	: m_leftTop(leftTop), m_width(width), m_height(height)
{
}

void CRectangle::DrawImpl(ICanvas& canvas) const
{
	canvas.MoveTo(m_leftTop);	
	canvas.LineTo({ m_leftTop.x + m_width, m_leftTop.y });
	canvas.LineTo({ m_leftTop.x + m_width, m_leftTop.y + m_height });
	canvas.LineTo({ m_leftTop.x, m_leftTop.y + m_height });
	canvas.LineTo({ m_leftTop.x, m_leftTop.y });
	
}

RectD CRectangle::GetFrame()
{
	return { m_leftTop, m_width, m_height };
}

void CRectangle::SetFrame(RectD const& rect)
{
	m_leftTop = rect.leftTop;
	m_width = rect.width;
	m_height = rect.height;
}
