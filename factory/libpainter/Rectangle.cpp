#include "stdafx.h"
#include "Rectangle.h"

CRectangle::CRectangle(CPoint const& leftTop, CPoint const& rightBottom, Color color)
	: CShape(color)
	, m_leftTop(leftTop)
	, m_rightBottom(rightBottom)
{
	if (leftTop.x >= rightBottom.x || leftTop.y >= rightBottom.y)
	{
		throw std::logic_error("Incorrect rectangle size");
	}
}

void CRectangle::DrawImpl(ICanvas & canvas)const
{	
	CPoint leftBottom = CPoint(m_leftTop.x, m_rightBottom.y);
	CPoint rightTop = CPoint(m_rightBottom.x, m_leftTop.y);

	canvas.DrawLine(m_leftTop, rightTop);
	canvas.DrawLine(rightTop, m_rightBottom);
	canvas.DrawLine(m_rightBottom, leftBottom);
	canvas.DrawLine(leftBottom, m_leftTop);
}

CPoint CRectangle::GetLeftTop()const
{
	return m_leftTop;
}

CPoint CRectangle::GetRightBottom()const
{
	return m_rightBottom;
}