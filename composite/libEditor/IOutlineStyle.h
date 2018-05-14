#pragma once
#include "IStyle.h"

class IOutlineStyle : public IStyle
{
public:
	virtual double GetStrokeWidth() const = 0;
	virtual void SetStrokeWidth(double width) = 0;

	virtual ~IOutlineStyle() = default;
};