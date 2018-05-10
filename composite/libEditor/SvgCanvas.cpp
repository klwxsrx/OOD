#include "stdafx.h"
#include "SvgCanvas.h"

void CSvgCanvas::SetLineColor(RGBAColor color)
{
	m_currentOutlineColor = color;
}

void CSvgCanvas::BeginFill(RGBAColor color)
{
	m_fillEnabled = true;
	m_currentFillColor = color;
	m_currentPolyline.clear();
}

void CSvgCanvas::EndFill()
{
	m_fillEnabled = false;
	DrawFill();
}

void CSvgCanvas::MoveTo(PointD const& point)
{
	m_currentPoint = point;
	if (m_fillEnabled)
	{
		m_currentPolyline.push_back(point);
	}
}

void CSvgCanvas::LineTo(PointD const& point)
{
	m_canvas << "<line x1=\"" << m_currentPoint.x << "\" y1=\"" << m_currentPoint.y << "\" x2=\"" << point.x << "\" y2=\"" << point.y
		<< "\" stroke=\"#" << std::hex << std::setw(8) << std::setfill('0') << m_currentOutlineColor << std::dec << "\" stroke-width=\"2\" />";
	MoveTo(point);
}

void CSvgCanvas::DrawEllipse(PointD const& center, double horizontalRadius, double verticalRadius)
{
	m_canvas << "<ellipse cx=\"" << center.x << "\" cy=\"" << center.y << "\" rx=\"" << horizontalRadius << "\" ry=\"" << verticalRadius
		<< "\" fill=\"#" << std::hex << std::setw(8) << std::setfill('0') << m_currentFillColor << std::dec << "\""
		<< " stroke=\"#" << std::hex << std::setw(8) << std::setfill('0') << m_currentOutlineColor << std::dec << "\" stroke-width=\"2\" />";
}

std::string CSvgCanvas::GetResult()const
{
	std::stringstream svg;
	svg	<< "<svg version = \"1.1\" width=\"100%\" height=\"100%\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" x=\"0px\" y=\"0px\">"
		<< m_canvas.str() << "</svg>";
	return svg.str();
}

void CSvgCanvas::DrawFill()
{
	m_canvas << "<polyline points=\"";
	for (PointD const& point : m_currentPolyline)
	{
		m_canvas << point.x << "," << point.y << " ";
	}
	m_canvas << "\" fill=\"#" << std::hex << std::setw(8) << std::setfill('0') << m_currentFillColor << std::dec << "\" stroke=\"none\" />";
	m_currentPolyline.clear();
}