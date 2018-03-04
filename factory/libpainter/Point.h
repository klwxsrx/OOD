#pragma once

struct CPoint
{
	CPoint(unsigned x, unsigned y)
		: x(x), y(y)
	{
	}
	CPoint(CPoint && point)
		: x(point.x), y(point.y)
	{
	}
	CPoint(CPoint const& point)
		: x(point.x), y(point.y)
	{
	}
	bool operator==(CPoint const& p)const
	{
		return p.x == x && p.y == y;
	}
	bool operator!=(CPoint const& p)const
	{
		return !(this == &p);
	}
	CPoint& operator=(CPoint && point)
	{
		x = point.x;
		y = point.y;
		return *this;
	}
	CPoint& operator=(CPoint const& point)
	{
		x = point.x;
		y = point.y;
		return *this;
	}
	unsigned x, y;
};