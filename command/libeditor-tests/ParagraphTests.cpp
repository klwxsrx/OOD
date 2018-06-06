#include "stdafx.h"
#include "../libeditor/IFileResource.h"
#include "../libeditor/Paragraph.h"
#include "../libeditor/History.h"

BOOST_AUTO_TEST_SUITE(Paragraph)

	BOOST_AUTO_TEST_CASE(can_be_created_with_description)
	{
		CHistory history;
		const std::string text("Test!");
		CParagraph paragraph(text, history);
		BOOST_CHECK_EQUAL(paragraph.GetText(), text);
	}

	BOOST_AUTO_TEST_CASE(can_set_text)
	{
		CHistory history;
		CParagraph paragraph("", history);

		const std::string text("Test!");
		paragraph.SetText(text);
		BOOST_CHECK_EQUAL(paragraph.GetText(), text);

		const std::string text1("Test1!");
		paragraph.SetText(text1);
		BOOST_CHECK_EQUAL(paragraph.GetText(), text1);
	}

	BOOST_AUTO_TEST_CASE(can_be_compared)
	{
		CHistory history;
		CParagraph paragraph1("Test", history);
		CParagraph paragraph2("Test", history);
		CParagraph paragraph3("Test1", history);

		BOOST_CHECK(paragraph1 == paragraph2);
		BOOST_CHECK(!(paragraph1 == paragraph3));
	}

BOOST_AUTO_TEST_SUITE_END()