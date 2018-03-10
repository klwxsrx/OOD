#include "stdafx.h"
#include "Shape.h"


CShape::CShape(Color color)
	: m_color(color)
{
}

void CShape::Draw(ICanvas & canvas)const
{
	canvas.SetColor(m_color);
	DrawImpl(canvas);
}

Color CShape::GetColor()const
{
	return m_color;
}
