#pragma once
#include "Shape.h"

class CRegularPolygon : public CShape
{
public:
	CRegularPolygon(CPoint const& center, unsigned radius, unsigned vertexCount, Color color);

	CPoint GetCenter()const;
	unsigned GetVertexCount() const;
	unsigned GetRadius()const;

protected:
	void DrawImpl(ICanvas & canvas)override;

private:
	CPoint m_center;
	unsigned m_radius, m_vertexCount;
};