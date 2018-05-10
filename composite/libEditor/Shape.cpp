#include "stdafx.h"
#include "Shape.h"

CShape::CShape()
	: m_fillStyle(false, Color::TRANSPARENT_COLOR), m_outlineStyle(true, Color::BLACK_COLOR)
{
}

void CShape::Draw(ICanvas& canvas) const
{
	canvas.SetLineColor(m_outlineStyle.IsEnabled() ? m_outlineStyle.GetColor().value() : Color::TRANSPARENT_COLOR);
	canvas.BeginFill(m_fillStyle.IsEnabled() ? m_fillStyle.GetColor().value() : Color::TRANSPARENT_COLOR);
	DrawImpl(canvas);
	canvas.EndFill();
}

IStyle& CShape::GetOutlineStyle()
{
	return m_outlineStyle;
}

const IStyle& CShape::GetOutlineStyle() const
{
	return m_outlineStyle;
}

IStyle& CShape::GetFillStyle()
{
	return m_fillStyle;
}

const IStyle& CShape::GetFillStyle() const
{
	return m_fillStyle;
}

std::shared_ptr<IGroupShape> CShape::GetGroup()
{
	return nullptr;
}

std::shared_ptr<const IGroupShape> CShape::GetGroup() const
{
	return nullptr;
}