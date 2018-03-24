#include "stdafx.h"
#include "../libeditor/IFileResource.h"
#include "../libeditor/Paragraph.h"

BOOST_AUTO_TEST_SUITE(Paragraph)

	BOOST_AUTO_TEST_CASE(can_be_created_with_description)
	{
		const std::string text("Test!");
		CParagraph paragraph(text);
		BOOST_CHECK_EQUAL(paragraph.GetText(), text);
	}

	BOOST_AUTO_TEST_CASE(can_set_text)
	{
		CParagraph paragraph("");

		const std::string text("Test!");
		paragraph.SetText(text);
		BOOST_CHECK_EQUAL(paragraph.GetText(), text);
	}

BOOST_AUTO_TEST_SUITE_END()