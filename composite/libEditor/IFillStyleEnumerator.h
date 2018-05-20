#pragma once
#include "IShape.h"

class IFillStyleEnumerator
{
public:
	virtual void EnumerateFillStyles(std::function<bool(IStyle&)> func) const = 0;

	virtual ~IFillStyleEnumerator() = default;
};