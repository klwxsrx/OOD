#pragma once
#include "../libpainter/Point.h"
#include "../libpainter/Color.h"
#include "../libpainter/IShape.h"

class CTestShape : public IShape
{
public:
	CTestShape(CPoint const& pointFrom, CPoint const& pointTo, CPoint const& center, unsigned horizontalRadius, unsigned verticalRadius, Color color)
		: m_pointFrom(pointFrom)
		, m_pointTo(pointTo)
		, m_center(center)
		, m_horizontalRadius(horizontalRadius)
		, m_verticalRadius(verticalRadius)
		, m_color(color)
	{
	}
	void Draw(ICanvas & canvas)const override
	{
		canvas.SetColor(m_color);
		canvas.DrawLine(m_pointFrom, m_pointTo);
		canvas.DrawEclipse(m_center, m_horizontalRadius, m_verticalRadius);
	}
	CPoint m_pointFrom, m_pointTo, m_center;
	unsigned m_horizontalRadius, m_verticalRadius;
	Color m_color;
};