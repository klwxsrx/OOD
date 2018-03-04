#pragma once
#include "Color.h"
#include "Point.h"

struct ICanvas
{
	virtual ~ICanvas() = default;

	virtual void SetColor(Color color) = 0;
	virtual void DrawLine(CPoint const& from, CPoint const& to) = 0;
	virtual void DrawEclipse(CPoint const& center, unsigned horizontalRadius, unsigned verticalRadius) = 0;
};