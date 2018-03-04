#pragma once
#include "../libpainter/Color.h"
#include "../libpainter/ICanvas.h"

class CTestCanvas : public ICanvas
{
public:
	void SetColor(Color color)override
	{
		m_canvasColor = color;
	}
	void DrawLine(CPoint const& from, CPoint const& to)override
	{
		m_lines.push_back(Line(from, to));
	}
	void DrawEclipse(CPoint const& center, unsigned horizontalRadius, unsigned verticalRadius)override
	{
		m_ellipses.push_back(Ellipse(center, horizontalRadius, verticalRadius));
	}
	Color GetColor()const
	{
		return m_canvasColor;
	}
	size_t GetLinesCount()const
	{
		return m_lines.size();
	}
	bool HasLine(CPoint const& start, CPoint const& end)const
	{
		return std::any_of(m_lines.begin(), m_lines.end(), [&](Line const& line) {
			return (line.start == start && line.end == end) || (line.start == end && line.end == start);
		});
	}
	size_t GetEllipsesCount()const
	{
		return m_ellipses.size();
	}
	bool HasEllipse(CPoint const& center, unsigned horizontalRadius, unsigned verticalRadius)const
	{
		return std::any_of(m_ellipses.begin(), m_ellipses.end(), [&](Ellipse const& ellipse) {
			return ellipse.center == center && ellipse.horizontalRadius == horizontalRadius && ellipse.verticalRadius == verticalRadius;
		});
	}

private:
	struct Line
	{
		Line(CPoint start, CPoint end)
			: start(start)
			, end(end)
		{
		}
		CPoint start, end;
	};
	struct Ellipse
	{
		Ellipse(CPoint const& center, unsigned horizontalRadius, unsigned verticalRadius)
			: center(center)
			, horizontalRadius(horizontalRadius)
			, verticalRadius(verticalRadius)
		{
		}
		CPoint center;
		unsigned horizontalRadius;
		unsigned verticalRadius;
	};

private:
	Color m_canvasColor;
	std::vector<Line> m_lines;
	std::vector<Ellipse> m_ellipses;
};