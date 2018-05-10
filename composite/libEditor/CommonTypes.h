#pragma once
#include <stdint.h>

template <typename T>
struct Point
{
	T x, y;
};

template <typename T>
struct Rect
{
	Point<T> leftTop;
	T width;
	T height;
};

typedef Point<double> PointD;
typedef Rect<double> RectD;
typedef uint32_t RGBAColor;

namespace Color
{
	static const uint32_t TRANSPARENT_COLOR = 0xFFFFFF00;
	static const uint32_t BLACK_COLOR = 0x000000FF;
}