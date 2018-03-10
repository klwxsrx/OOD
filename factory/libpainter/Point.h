#pragma once

struct CPoint
{
	CPoint();
	CPoint(unsigned x, unsigned y);
	CPoint(CPoint && point) = default;
	CPoint(CPoint const& point) = default;

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

std::istream& operator>>(std::istream& stream, CPoint& point);