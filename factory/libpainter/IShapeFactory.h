#pragma once
#include <memory>
#include <string>
#include "IShape.h"

struct IShapeFactory
{
	virtual ~IShapeFactory() = default;

	virtual std::unique_ptr<IShape> CreateShape(const std::string & description) = 0;
};