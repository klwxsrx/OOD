#include "stdafx.h"
#include "MockFileResource.h"
#include "../libeditor/IFileResource.h"
#include "../libeditor/Image.h"

struct Image_
{
	CImage image;
	Image_()
		: image(std::make_shared<CMockFileResource>(), 640u, 480u)
	{
		auto onChange = [](ImageSize& image, ImageSize const& imageSize) {
			image = imageSize;
		};
		image.ConnectOnResize(onChange);
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

BOOST_AUTO_TEST_SUITE_END()