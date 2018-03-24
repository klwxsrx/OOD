#pragma once
#include <memory>
#include <boost/filesystem.hpp>

class IFileResource
{
public:
	typedef std::shared_ptr<IFileResource> Ptr;

	virtual boost::filesystem::path GetPath()const = 0;

	virtual ~IFileResource() = default;
};