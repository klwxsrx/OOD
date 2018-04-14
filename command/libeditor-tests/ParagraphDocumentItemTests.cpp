#include "stdafx.h"
#include "../libeditor/ParagraphDocumentItem.h"

struct ParagraphDocumentItemFixture
{
	std::shared_ptr<CParagraph> paragraph;
	CParagraphDocumentItem item;
	CParagraphDocumentItem* itemPtr;
	CParagraphDocumentItem const* itemConstPtr;
	ParagraphDocumentItemFixture()
		: paragraph(std::make_shared<CParagraph>("Some text"))
		, item(paragraph), itemPtr(&item), itemConstPtr(&item)
	{
	}
};

BOOST_AUTO_TEST_SUITE(ParagraphDocumentItem)
	
	BOOST_AUTO_TEST_CASE(returns_description_of_paragraph)
	{
		CParagraphDocumentItem item("Test!");
		BOOST_CHECK_EQUAL(item.GetDescription(), "Paragraph: Test!");
	}

	BOOST_FIXTURE_TEST_CASE(returns_paragraph, ParagraphDocumentItemFixture)
	{
		BOOST_CHECK(item.GetParagraph() == paragraph);
		BOOST_CHECK(itemConstPtr->GetParagraph() == paragraph);
	}

	BOOST_FIXTURE_TEST_CASE(returns_empty_image_ptr, ParagraphDocumentItemFixture)
	{
		BOOST_CHECK(itemPtr->GetImage() == nullptr);
		BOOST_CHECK(itemConstPtr->GetImage() == nullptr);
	}

BOOST_AUTO_TEST_SUITE_END()