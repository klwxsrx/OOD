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

struct RgbColor
{
	RgbColor()
	{
		r = 0;
		g = 0;
		b = 0;
	}
	RgbColor(Color color)
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

	unsigned r, g, b;
};