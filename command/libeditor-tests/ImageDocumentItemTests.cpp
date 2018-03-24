#include "stdafx.h"
#include "MockFileResource.h"
#include "../libeditor/ImageDocumentItem.h"

BOOST_AUTO_TEST_SUITE(ImageDocumentItem)
	
	BOOST_AUTO_TEST_CASE(returns_description_of_image)
	{
		CImageDocumentItem item(std::make_shared<CMockFileResource>(), 640u, 480u);
		BOOST_CHECK_EQUAL(item.GetDescription(), "Image: 640 480 \"" + CMockFileResource::PATH + "\"");
	}

BOOST_AUTO_TEST_SUITE_END()