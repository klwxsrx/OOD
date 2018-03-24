#include "stdafx.h"
#include "MockFileResource.h"

boost::filesystem::path CMockFileResource::GetPath()const
{
	return boost::filesystem::path(PATH);
}

std::string const CMockFileResource::PATH = "Test!!!";