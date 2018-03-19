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

std::istream& operator>>(std::istream& stream, Color& color);

struct RgbColor
{
	RgbColor();
	RgbColor(Color color);

	unsigned r, g, b;
};