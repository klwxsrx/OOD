#include "stdafx.h"
#include "../libeditor/FileResource.h"
#include "../libeditor/FileUtils.h"

void CreateFile(boost::filesystem::path const& path)
{
	BOOST_CHECK_NO_THROW(boost::filesystem::ofstream(path.string()));
}

void SetFileReadPermissions(boost::filesystem::path const& path)
{
	BOOST_CHECK_NO_THROW(permissions(path, boost::filesystem::perms::owner_read));
}

struct CreatedFileFixture
{
	const boost::filesystem::path path;
	CreatedFileFixture()
		: path("test.file")
	{
		DeleteFile();
	}
	~CreatedFileFixture()
	{
		DeleteFile();		
	}
	void DeleteFile()
	{
		try
		{
			permissions(path, boost::filesystem::perms::owner_all);
			FileUtils::Delete(path);
		}
		catch (std::runtime_error const&)
		{
		}
	}
};

BOOST_FIXTURE_TEST_SUITE(File_resource, CreatedFileFixture)

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
	}

	BOOST_AUTO_TEST_CASE(not_throws_error_when_cant_delete_file)
	{
		CreateFile(path);
		SetFileReadPermissions(path);

		BOOST_CHECK_NO_THROW({
			CFileResource resource(path);
		});
		BOOST_CHECK(boost::filesystem::exists(path));
	}

BOOST_AUTO_TEST_SUITE_END()