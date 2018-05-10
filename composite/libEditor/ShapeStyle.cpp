#include "stdafx.h"
#include "ShapeStyle.h"

CShapeStyle::CShapeStyle(bool isEnabled, RGBAColor color)
	: m_isEnabled(isEnabled), m_color(color)
{
}

boost::optional<bool> CShapeStyle::IsEnabled() const
{
	return m_isEnabled;
}

void CShapeStyle::Enable(bool enable)
{
	m_isEnabled = enable;
}

boost::optional<RGBAColor> CShapeStyle::GetColor() const
{
	return m_color;
}

void CShapeStyle::SetColor(RGBAColor color)
{
	m_color = color;
}
