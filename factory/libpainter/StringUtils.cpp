#include "stdafx.h"
#include "StringUtils.h"

unsigned StrToUnsignedInt(std::string const& str)
{
	unsigned result = 0;
	try
	{
		if (str.empty())
		{
			throw std::exception();
		}
		result = std::stoul(str);
	}
	catch (std::exception const&)
	{
		throw std::runtime_error("Value must be unsigned integer");
	}

	return result;
}