#include "stdafx.h"
#include "Triangle.h"

CTriangle::CTriangle(CPoint const& vertex1, CPoint const& vertex2, CPoint const& vertex3, Color color)
	: m_vertex1(vertex1)
	, m_vertex2(vertex2)
	, m_vertex3(vertex3)
	, CShape(color)
{
	if (m_vertex1 == m_vertex2 || m_vertex1 == m_vertex3 || m_vertex2 == m_vertex3)
	{
		throw std::logic_error("Wrong parameters");
	}
}

CPoint CTriangle::GetVertex1()const
{
	return m_vertex1;
}

CPoint CTriangle::GetVertex2()const
{
	return m_vertex2;
}

CPoint CTriangle::GetVertex3()const
{
	return m_vertex3;
}

void CTriangle::DrawImpl(ICanvas & canvas)const
{
	canvas.DrawLine(m_vertex1, m_vertex2);
	canvas.DrawLine(m_vertex2, m_vertex3);
	canvas.DrawLine(m_vertex3, m_vertex1);
}