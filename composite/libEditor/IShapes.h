#pragma once
#include <boost/optional.hpp>
#include "IShape.h"

class IShapes
{
public:
	virtual size_t GetShapesCount() const = 0;
	virtual void InsertShape(std::shared_ptr<IShape> const& shape, boost::optional<size_t> position = boost::none) = 0;
	virtual std::shared_ptr<IShape> GetShapeAtIndex(size_t index) = 0;
	virtual void RemoveShapeAtIndex(size_t index) = 0;

	virtual ~IShapes() = default;
};