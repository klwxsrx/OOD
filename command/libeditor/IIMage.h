#pragma once
#include <boost\filesystem.hpp>

class IImage
{
public:
	virtual boost::filesystem::path GetPath()const = 0;

	virtual unsigned GetWidth()const = 0;
	virtual unsigned GetHeight()const = 0;

	virtual void Resize(unsigned width, unsigned height) = 0;

	virtual ~IImage() = default;
};
