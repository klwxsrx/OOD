#include "stdafx.h"
#include "MockFileResource.h"
#include "../libeditor/IFileResource.h"
#include "../libeditor/Image.h"
#include "../libeditor/History.h"

struct Image_
{
	CHistory history;
	CImage image;
	Image_()
		: image(std::make_shared<CMockFileResource>(), ImageSize(640u, 480u), history)
	{
	}
};

BOOST_FIXTURE_TEST_SUITE(Image, Image_)

	BOOST_AUTO_TEST_CASE(returns_resource_path)
	{
		BOOST_CHECK_EQUAL(image.GetPath(), CMockFileResource::PATH);
	}

	BOOST_AUTO_TEST_CASE(returns_its_width_and_height)
	{
		BOOST_CHECK_EQUAL(image.GetWidth(), 640u);
		BOOST_CHECK_EQUAL(image.GetHeight(), 480u);
	}

	BOOST_AUTO_TEST_CASE(can_resize_its_width_and_height)
	{
		image.Resize(1024u, 768u);
		BOOST_CHECK_EQUAL(image.GetWidth(), 1024u);
		BOOST_CHECK_EQUAL(image.GetHeight(), 768u);
	}

	BOOST_AUTO_TEST_CASE(can_be_compared)
	{
		CHistory history;
		BOOST_CHECK(CImage(std::make_shared<CFileResource>("Path"), ImageSize(640u, 480u), history) == CImage(std::make_shared<CFileResource>("Path"), ImageSize(640u, 480u), history));

		BOOST_CHECK(!(CImage(std::make_shared<CFileResource>("Path"), ImageSize(640u, 480u), history) == CImage(std::make_shared<CFileResource>("Path1"), ImageSize(640u, 480u), history)));
		BOOST_CHECK(!(CImage(std::make_shared<CFileResource>("Path"), ImageSize(640u, 480u), history) == CImage(std::make_shared<CFileResource>("Path"), ImageSize(641u, 480u), history)));
		BOOST_CHECK(!(CImage(std::make_shared<CFileResource>("Path"), ImageSize(640u, 480u), history) == CImage(std::make_shared<CFileResource>("Path"), ImageSize(640u, 481u), history)));
	}

BOOST_AUTO_TEST_SUITE_END()