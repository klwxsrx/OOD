#include "stdafx.h"
#include "SvgCanvas.h"

void CSvgCanvas::SetColor(Color color)
{
	m_currentColor = RgbColor(color);
}

void CSvgCanvas::DrawLine(CPoint const& from, CPoint const& to)
{
	m_canvas << "<line x1=\"" << from.x << "\" y1=\"" << from.y << "\" x2=\"" << to.x << "\" y2=\"" << to.y
		<< "\" style=\"stroke:rgb(" << m_currentColor.r << ", " << m_currentColor.g << ", " << m_currentColor.b << ");stroke-width:2\"/>";
}

void CSvgCanvas::DrawEclipse(CPoint const& center, unsigned horizontalRadius, unsigned verticalRadius)
{
	m_canvas << "<ellipse cx=\"" << center.x << "\" cy=\"" << center.y << "\" rx=\"" << horizontalRadius << "\" ry=\"" << verticalRadius
		<< "\" style=\"fill:none; stroke:rgb(" << m_currentColor.r << ", "<< m_currentColor .g << ", " << m_currentColor .b << "); stroke - width:2\"/>";
}

std::string CSvgCanvas::GetResult()const
{
	std::stringstream svg;
	svg << "<?xml version=\"1.0\" encoding=\"utf - 8\"?><!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">"
		<< "<svg version = \"1.1\" width = \"100%\" height = \"100%\" xmlns = \"http://www.w3.org/2000/svg\" xmlns:xlink = \"http://www.w3.org/1999/xlink\" x=\"0px\" y=\"0px\">"
		<< m_canvas.str() << "</svg>";
	return svg.str();
}