#include "stdafx.h"
#include "../libeditor/Document.h"

struct EmptyDocumentFixture
{
	CDocument document;
};

BOOST_FIXTURE_TEST_SUITE(Document, EmptyDocumentFixture)

	BOOST_AUTO_TEST_CASE(returns_actual_size)
	{
		BOOST_CHECK_EQUAL(document.GetItemsCount(), 0);
		document.InsertParagraph("Test");
		BOOST_CHECK_EQUAL(document.GetItemsCount(), 1);
		document.InsertImage("test.jpg", 640, 480);
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
	}

BOOST_AUTO_TEST_SUITE_END()