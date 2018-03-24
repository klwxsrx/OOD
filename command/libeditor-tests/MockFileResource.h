#pragma once
#include "../libeditor/IFileResource.h"

class CMockFileResource : public IFileResource
{
public:
	static const std::string PATH;

	boost::filesystem::path GetPath()const override;
};