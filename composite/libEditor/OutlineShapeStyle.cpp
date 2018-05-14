#include "stdafx.h"
#include "OutlineShapeStyle.h"

COutlineShapeStyle::COutlineShapeStyle(bool isEnabled, RGBAColor color, double strokeWidth)
	: CShapeStyle(isEnabled, color), m_strokeWidth(strokeWidth)
{
}

boost::optional<double> COutlineShapeStyle::GetStrokeWidth() const
{
	return m_strokeWidth;
}

void COutlineShapeStyle::SetStrokeWidth(double width)
{
	m_strokeWidth = width;
}

boost::optional<bool> COutlineShapeStyle::IsEnabled() const
{
	return CShapeStyle::IsEnabled();
}

void COutlineShapeStyle::Enable(bool enable)
{
	CShapeStyle::Enable(enable);
}

boost::optional<RGBAColor> COutlineShapeStyle::GetColor() const
{
	return CShapeStyle::GetColor();
}

void COutlineShapeStyle::SetColor(RGBAColor color)
{
	return CShapeStyle::SetColor(color);
}
