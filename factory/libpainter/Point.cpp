#include "stdafx.h"
#include "Point.h"

CPoint::CPoint()
	: x(0), y(0)
{
}

CPoint::CPoint(unsigned x, unsigned y)
	: x(x), y(y)
{
}

std::istream& operator>>(std::istream& stream, CPoint& point)
{
	std::string pointStr;
	stream >> pointStr;

	std::vector<std::string> pointArr;
	boost::split(pointArr, pointStr, std::bind2nd(std::equal_to<char>(), ':'));

	if (pointArr.size() != 2)
	{
		throw std::runtime_error("Must be two int values in point!");
	}

	try
	{
		CPoint newPoint(StrToUnsignedInt(pointArr[0]), StrToUnsignedInt(pointArr[1]));
		std::swap(point, newPoint);
	}
	catch (std::exception const&)
	{
		throw std::runtime_error("Point value must be number");
	}

	return stream;
}