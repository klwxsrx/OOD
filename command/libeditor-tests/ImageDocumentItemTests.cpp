#include "stdafx.h"
#include "MockFileResource.h"
#include "../libeditor/ImageDocumentItem.h"

struct ImageDocumentItemFixture
{
	std::shared_ptr<CImage> image;
	CImageDocumentItem item;
	CImageDocumentItem* itemPtr;
	CImageDocumentItem const* itemConstPtr;
	ImageDocumentItemFixture()
		: image(std::make_shared<CImage>(std::make_shared<CMockFileResource>(), 640u, 480u))
		, item(image), itemPtr(&item), itemConstPtr(&item)
	{
	}
};

BOOST_AUTO_TEST_SUITE(ImageDocumentItem)
	
	BOOST_AUTO_TEST_CASE(returns_description_of_image)
	{
		CImageDocumentItem item(std::make_shared<CMockFileResource>(), 640u, 480u);
		BOOST_CHECK_EQUAL(item.GetDescription(), "Image: 640 480 \"" + CMockFileResource::PATH + "\"");

		CImageDocumentItem item1(std::make_shared<CImage>(std::make_shared<CMockFileResource>(), 640u, 480u));
		BOOST_CHECK_EQUAL(item1.GetDescription(), "Image: 640 480 \"" + CMockFileResource::PATH + "\"");
	}
	
	BOOST_FIXTURE_TEST_CASE(returns_image, ImageDocumentItemFixture)
	{
		BOOST_CHECK(itemPtr->GetImage() == image);
		BOOST_CHECK(itemConstPtr->GetImage() == image);
	}

	BOOST_FIXTURE_TEST_CASE(returns_empty_paragrap_ptr, ImageDocumentItemFixture)
	{
		BOOST_CHECK(itemPtr->GetParagraph() == nullptr);
		BOOST_CHECK(itemConstPtr->GetParagraph() == nullptr);
	}

BOOST_AUTO_TEST_SUITE_END()