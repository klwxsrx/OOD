#pragma once
#include <boost/optional.hpp>
#include "IShapes.h"

class IGroupShape : public IShape, public IShapes
{
public:
	virtual ~IGroupShape() = default;
};