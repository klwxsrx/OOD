#pragma once
#include <memory>
#include <vector>
#include <boost/iterator/indirect_iterator.hpp>
#include "IShape.h"

class IPictureDraft
{
public:
	virtual ~IPictureDraft() = default;

	typedef std::vector<std::unique_ptr<IShape>> Storage;
	typedef boost::indirect_iterator<Storage::const_iterator, const IShape&> ConstIterator;

	virtual void AddShape(std::unique_ptr<IShape> && shape) = 0;
	virtual bool IsEmpty()const = 0;

	virtual ConstIterator begin()const = 0;
	virtual ConstIterator end()const = 0;
};