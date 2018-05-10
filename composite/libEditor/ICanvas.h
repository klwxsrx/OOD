#pragma once
#include "CommonTypes.h"

class ICanvas
{
public:
	virtual void SetLineColor(RGBAColor color) = 0;
	virtual void BeginFill(RGBAColor color) = 0;
	virtual void EndFill() = 0;
	virtual void MoveTo(PointD const& point) = 0;
	virtual void LineTo(PointD const& point) = 0;
	virtual void DrawEllipse(PointD const& center, double horizontalRadius, double verticalRadius) = 0;

	virtual ~ICanvas() = default;
};