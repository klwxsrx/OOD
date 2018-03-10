#pragma once
#include "Color.h"
#include "ICanvas.h"

class IShape
{
public:
	virtual ~IShape() = default;

	virtual void Draw(ICanvas & canvas)const = 0;
};