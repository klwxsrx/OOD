#pragma once

enum class Color
{
	Green,
	Red,
	Blue,
	Yellow,
	Pink,
	Black,
};

struct CColor
{
	CColor();
	Color color;
};

std::istream& operator>>(std::istream& stream, CColor& color);

struct RgbColor
{
	RgbColor();
	RgbColor(Color color);

	unsigned r, g, b;
};