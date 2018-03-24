#include "stdafx.h"
#include "../libeditor/ParagraphDocumentItem.h"

BOOST_AUTO_TEST_SUITE(ParagraphDocumentItem)
	
	BOOST_AUTO_TEST_CASE(returns_description_of_paragraph)
	{
		CParagraphDocumentItem item("Test!");
		BOOST_CHECK_EQUAL(item.GetDescription(), "Paragraph: Test!");
	}

BOOST_AUTO_TEST_SUITE_END()