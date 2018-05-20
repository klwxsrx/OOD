#pragma once
#include "IShape.h"

class IOutlineStyleEnumerator
{
public:
	virtual void EnumerateOutlineStyles(std::function<bool(IOutlineStyle&)> func) const = 0;

	virtual ~IOutlineStyleEnumerator() = default;
};
