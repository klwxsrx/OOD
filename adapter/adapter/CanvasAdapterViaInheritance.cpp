#include "stdafx.h"
#include "CanvasAdapterViaInheritance.h"

CCanvasAdapterViaInheritance::CCanvasAdapterViaInheritance(std::ostream& out)
	: modern_graphics_lib::CModernGraphicsRenderer(out), m_currentPoint(0, 0), m_color({ 0, 0, 0, 1 })
{
	BeginDraw();
}

void CCanvasAdapterViaInheritance::MoveTo(int x, int y)
{
	m_currentPoint.x = x;
	m_currentPoint.y = y;
}

void CCanvasAdapterViaInheritance::LineTo(int x, int y)
{
	DrawLine(m_currentPoint, { x, y }, m_color);
	MoveTo(x, y);
}

void CCanvasAdapterViaInheritance::SetColor(uint32_t rgbColor)
{
	uint8_t red = (rgbColor & 0xFF000000) >> 24;
	uint8_t green = (rgbColor & 0x00FF0000) >> 16;
	uint8_t blue = (rgbColor & 0x0000FF00) >> 8;
	uint8_t opacity = rgbColor & 0x000000FF;

	m_color.r = PrepareColorValue(red);
	m_color.g = PrepareColorValue(green);
	m_color.b = PrepareColorValue(blue);
	m_color.a = PrepareColorValue(opacity);
}

float CCanvasAdapterViaInheritance::PrepareColorValue(uint8_t value)
{
	static const auto maxValue = std::numeric_limits<uint8_t>::max();
	return static_cast<float>(value) / maxValue;
}