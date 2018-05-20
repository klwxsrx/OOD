#include "stdafx.h"
#include "Ellipse.h"

CEllipse::CEllipse(PointD const& center, double horizontalRadius, double verticalRadius)
	: m_center(center), m_horizontalRadius(horizontalRadius), m_verticalRadius(verticalRadius)
{
}

void CEllipse::DrawImpl(ICanvas& canvas) const
{
	canvas.MoveTo(m_center);
	canvas.DrawEllipse(m_center, m_horizontalRadius, m_verticalRadius);
}

RectD CEllipse::GetFrame() const
{
	return { { m_center.x - m_horizontalRadius, m_center.y - m_verticalRadius }, m_horizontalRadius * 2, m_verticalRadius * 2 };
}

void CEllipse::SetFrame(RectD const& rect)
{
	const RectD currentFrame = GetFrame();

	const double horizontalScale = rect.width / currentFrame.width;
	const double verticalScale = rect.height / currentFrame.height;

	m_horizontalRadius *= horizontalScale;
	m_verticalRadius *= verticalScale;

	m_center.x = rect.leftTop.x + m_horizontalRadius;
	m_center.y = rect.leftTop.y + m_verticalRadius;
}