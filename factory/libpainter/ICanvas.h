#pragma once
#include "Color.h"

struct CPoint;

struct ICanvas
{
	virtual void SetColor(Color color) = 0;
	virtual void DrawLine(CPoint const& from, CPoint const& to) = 0;
	virtual void DrawEclipse(CPoint const& center, unsigned horizontalRadius, unsigned verticalRadius) = 0;
};