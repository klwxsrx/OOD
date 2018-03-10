#include "stdafx.h"
#include "RegularPolygon.h"

const unsigned FULL_ANGLE = 360;

CRegularPolygon::CRegularPolygon(CPoint const& center, unsigned radius, unsigned vertexCount, Color color)
	: m_center(center)
	, m_radius(radius)
	, m_vertexCount(vertexCount)
	, CShape(color)
{
	if (radius == 0 || vertexCount < 3)
	{
		throw std::logic_error("WrongParameters");
	}
}

CPoint CRegularPolygon::GetCenter()const
{
	return m_center;
}

unsigned CRegularPolygon::GetVertexCount() const
{
	return m_vertexCount;
}

unsigned CRegularPolygon::GetRadius()const
{
	return m_radius;
}

void CRegularPolygon::DrawImpl(ICanvas & canvas)
{
	const double stepAngle = M_PI / m_vertexCount * 2;
	double currentAngle = (M_PI / 2) + stepAngle;

	CPoint topPoint(m_center.x, m_center.y - m_radius);
	CPoint previousPoint(topPoint);
	for (unsigned i = 0; i < m_vertexCount - 1; ++i)
	{
		const unsigned x = m_center.x + static_cast<unsigned>(ceil(m_radius * cos(currentAngle)));
		const unsigned y = m_center.y - static_cast<unsigned>(ceil(m_radius * sin(currentAngle)));

		CPoint point(x, y);
		canvas.DrawLine(previousPoint, point);

		previousPoint = std::move(point);
		currentAngle += stepAngle;
	}
	canvas.DrawLine(previousPoint, topPoint);
}