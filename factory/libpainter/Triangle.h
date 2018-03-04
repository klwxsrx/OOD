#pragma once
#include "Shape.h"

class CTriangle : public CShape
{
public:
	CTriangle(CPoint const& vertex1, CPoint const& vertex2, CPoint const& vertex3, Color color);
	
	CPoint GetVertex1()const;
	CPoint GetVertex2()const;
	CPoint GetVertex3()const;

protected:
	void DrawImpl(ICanvas & canvas)override;

private:
	CPoint m_vertex1, m_vertex2, m_vertex3;
};