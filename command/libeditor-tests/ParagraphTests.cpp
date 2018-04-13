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
		auto onChange = [](std::string& oldText, std::string const& newText) {
			oldText = newText;
		};
		CParagraph paragraph("");
		paragraph.ConnectOnChange(onChange);

		const std::string text("Test!");
		paragraph.SetText(text);
		BOOST_CHECK_EQUAL(paragraph.GetText(), text);
		
		paragraph.ConnectOnChange([](std::string&, std::string const&) {
			BOOST_CHECK(false);
		});
		paragraph.SetText(text); // text will not change
	}

BOOST_AUTO_TEST_SUITE_END()