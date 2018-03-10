#include "stdafx.h"
#include "Color.h"

CColor::CColor()
	: color(Color::Black)
{
}

std::istream& operator>>(std::istream& stream, CColor& color)
{
	static const std::map<std::string, Color> colorMap({
		{ "Black", Color::Black },
		{ "Blue", Color::Blue },
		{ "Green", Color::Green },
		{ "Pink", Color::Pink },
		{ "Red", Color::Red },
		{ "Yellow", Color::Yellow }
	});

	std::string colorStr;
	stream >> colorStr;

	if (colorStr.empty())
	{
		throw std::runtime_error("Empty color");
	}

	auto it = colorMap.find(colorStr);
	if (it == colorMap.end())
	{
		throw std::runtime_error("Invalid color!");
	}

	color.color = it->second;
	
	return stream;
}

RgbColor::RgbColor()
{
	r = 0;
	g = 0;
	b = 0;
}

RgbColor::RgbColor(Color color)
{
	switch (color)
	{
	case Color::Green:
		r = 0;
		g = 255;
		b = 0;
		break;
	case Color::Red:
		r = 255;
		g = 0;
		b = 0;
		break;
	case Color::Blue:
		r = 0;
		g = 0;
		b = 255;
		break;
	case Color::Yellow:
		r = 255;
		g = 255;
		b = 0;
		break;
	case Color::Pink:
		r = 255;
		g = 203;
		b = 219;
		break;
	case Color::Black:
	default:
		r = 0;
		g = 0;
		b = 0;
		break;
	}
}