#include "stdafx.h"
#include "../libeditor/FileResource.h"

void CreateFile(boost::filesystem::path const& path)
{
	boost::filesystem::ofstream(path.string());
	BOOST_CHECK(boost::filesystem::exists(path));
}

void DeleteFileIfExist(boost::filesystem::path const& path)
{
	boost::filesystem::remove(path);
}

struct Path
{
	const boost::filesystem::path path;
	Path()
		: path("test.file")
	{
	}
};

BOOST_FIXTURE_TEST_SUITE(File_resource, Path)

	BOOST_AUTO_TEST_CASE(can_return_its_path)
	{
		CFileResource resource(path);
		BOOST_CHECK_EQUAL(resource.GetPath(), path);
	}

	BOOST_AUTO_TEST_CASE(can_delete_file)
	{
		CreateFile(path);

		{
			CFileResource resource(path);
		}

		BOOST_CHECK(!boost::filesystem::exists(path));
		DeleteFileIfExist(path);
	}

	BOOST_AUTO_TEST_CASE(not_throws_error_when_cant_delete_file)
	{
		// TODO: 
	}

BOOST_AUTO_TEST_SUITE_END()