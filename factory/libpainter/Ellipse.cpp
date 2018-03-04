#include "stdafx.h"
#include "Ellipse.h"

CEllipse::CEllipse(CPoint const& center, unsigned horizontalRadius, unsigned verticalRadius, Color color)
	: m_center(center)
	, m_horizontalRadius(horizontalRadius)
	, m_verticalRadius(verticalRadius)
	, CShape(color)
{
	if (m_horizontalRadius == 0 || m_verticalRadius == 0)
	{
		throw std::logic_error("Wrong parameters");
	}
}

CPoint CEllipse::GetCenter()const
{
	return m_center;
}

unsigned CEllipse::GetHorizontalRadius()const
{
	return m_horizontalRadius;
}

unsigned CEllipse::GetVerticalRadius()const
{
	return m_verticalRadius;
}

void CEllipse::DrawImpl(ICanvas & canvas)
{
	canvas.DrawEclipse(m_center, m_horizontalRadius, m_verticalRadius);
}