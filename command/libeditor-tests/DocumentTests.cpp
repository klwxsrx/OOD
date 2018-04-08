#include "stdafx.h"
#include "../libeditor/Document.h"

struct EmptyDocumentFixture
{
	CDocument document;
};

BOOST_FIXTURE_TEST_SUITE(Document, EmptyDocumentFixture)

	BOOST_AUTO_TEST_CASE(has_default_title)
	{
		BOOST_CHECK_EQUAL(document.GetTitle(), "Untitled document");
	}

	BOOST_AUTO_TEST_CASE(can_set_new_title)
	{
		std::string title = "Test title 1";
		document.SetTitle(title);
		BOOST_CHECK_EQUAL(document.GetTitle(), title);
	}

	/*BOOST_AUTO_TEST_CASE(returns_actual_size)
	{
		BOOST_CHECK_EQUAL(document.GetItemsCount(), 0);
		document.InsertParagraph("test1");
		BOOST_CHECK_EQUAL(document.GetItemsCount(), 1);
		document.InsertImage("testPath", 640, 480);
		BOOST_CHECK_EQUAL(document.GetItemsCount(), 2);
		document.DeleteItem(0);
		BOOST_CHECK_EQUAL(document.GetItemsCount(), 1);
		document.DeleteItem(0);
		BOOST_CHECK_EQUAL(document.GetItemsCount(), 0);

		document.Undo();
		BOOST_CHECK_EQUAL(document.GetItemsCount(), 1);
		document.Undo();
		BOOST_CHECK_EQUAL(document.GetItemsCount(), 2);
		document.Redo();
		BOOST_CHECK_EQUAL(document.GetItemsCount(), 1);
		document.Undo();
		BOOST_CHECK_EQUAL(document.GetItemsCount(), 2);
		document.Redo();
		BOOST_CHECK_EQUAL(document.GetItemsCount(), 1);
		document.Redo();
		BOOST_CHECK_EQUAL(document.GetItemsCount(), 0);
	}*/

BOOST_AUTO_TEST_SUITE_END()