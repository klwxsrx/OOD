#include "stdafx.h"
#include "../libeditor/Document.h"
#include "../libeditor/FileUtils.h"

struct EmptyDocumentFixture
{
	CDocument document;
	const std::string DEFAULT_DOCUMENT_TITLE = "Untitled document";
	const std::string TEST_IMAGE_PATH = "test.jpg";
};

struct DocumentWithInsertedParagraph : EmptyDocumentFixture
{
	const std::string PARAGRAPH_TEXT = "Some paragraph text";
	DocumentWithInsertedParagraph()
	{
		document.InsertParagraph(PARAGRAPH_TEXT);
	}
};

struct DocumentWithDeletedItem : DocumentWithInsertedParagraph
{
	DocumentWithDeletedItem()
	{
		document.DeleteItem(0);
	}
};

struct DocumentWithDeletedItemAfterUndo : DocumentWithDeletedItem
{
	DocumentWithDeletedItemAfterUndo()
	{
		document.Undo();
	}
};

struct DocumentWithDeletedItemAfterUndoAndRedo : DocumentWithDeletedItemAfterUndo
{
	DocumentWithDeletedItemAfterUndoAndRedo()
	{
		document.Redo();
	}
};

struct DocumentWithDeletedItemAfterUndoDeletedFromHistory : DocumentWithDeletedItemAfterUndo
{
	DocumentWithDeletedItemAfterUndoDeletedFromHistory()
	{
		document.SetTitle("Test"); // execute some command to delete undo`ed command from history
	}
};

BOOST_AUTO_TEST_SUITE(Document)

	BOOST_FIXTURE_TEST_SUITE(when_item_is_deleted, DocumentWithDeletedItem)

		BOOST_AUTO_TEST_CASE(returns_zero_count)
		{
			BOOST_CHECK_EQUAL(document.GetItemsCount(), 0);
		}

		BOOST_AUTO_TEST_CASE(cant_get_item)
		{
			CDocument const* documentPtr = &document;
			BOOST_CHECK_THROW(document.GetItem(0), std::runtime_error);
			BOOST_CHECK_THROW(documentPtr->GetItem(0), std::runtime_error);
		}

		BOOST_AUTO_TEST_CASE(returns_true_when_check_undo)
		{
			BOOST_CHECK(document.CanUndo());
		}

		BOOST_AUTO_TEST_CASE(can_undo)
		{
			BOOST_CHECK_NO_THROW(document.Undo());
			BOOST_CHECK_EQUAL(document.GetItemsCount(), 1);
			BOOST_CHECK_EQUAL(document.GetItem(0)->GetParagraph()->GetText(), PARAGRAPH_TEXT);
		}

		BOOST_AUTO_TEST_CASE(returns_false_when_check_redo)
		{
			BOOST_CHECK(!document.CanRedo());
		}

		BOOST_AUTO_TEST_CASE(cant_redo)
		{
			BOOST_CHECK_THROW(document.Redo(), std::runtime_error);
			BOOST_CHECK_EQUAL(document.GetItemsCount(), 0);
		}

		BOOST_FIXTURE_TEST_SUITE(after_undo, DocumentWithDeletedItemAfterUndo)
			
			BOOST_AUTO_TEST_CASE(returns_one_items_count)
			{
				BOOST_CHECK_EQUAL(document.GetItemsCount(), 1);
			}

			BOOST_AUTO_TEST_CASE(can_get_item)
			{
				CDocument const* documentPtr = &document;
				BOOST_CHECK_EQUAL(document.GetItem(0)->GetParagraph()->GetText(), PARAGRAPH_TEXT);
				BOOST_CHECK_EQUAL(documentPtr->GetItem(0)->GetParagraph()->GetText(), PARAGRAPH_TEXT);
			}

			BOOST_AUTO_TEST_CASE(returns_true_when_check_undo)
			{
				BOOST_CHECK(document.CanUndo());
			}

			BOOST_AUTO_TEST_CASE(can_undo)
			{
				BOOST_CHECK_NO_THROW(document.Undo());
				BOOST_CHECK_EQUAL(document.GetItemsCount(), 0);
			}

			BOOST_AUTO_TEST_CASE(returns_true_when_check_redo)
			{
				BOOST_CHECK(document.CanRedo());
			}

			BOOST_AUTO_TEST_CASE(can_redo)
			{
				BOOST_CHECK_NO_THROW(document.Undo());
				BOOST_CHECK_EQUAL(document.GetItemsCount(), 0);
			}

			BOOST_FIXTURE_TEST_SUITE(after_redo, DocumentWithDeletedItemAfterUndoAndRedo)

				BOOST_AUTO_TEST_CASE(returns_zero_count)
				{
					BOOST_CHECK_EQUAL(document.GetItemsCount(), 0);
				}

				BOOST_AUTO_TEST_CASE(cant_get_item)
				{
					BOOST_CHECK_THROW(document.GetItem(0), std::runtime_error);
				}

				BOOST_AUTO_TEST_CASE(returns_true_when_check_undo)
				{
					BOOST_CHECK(document.CanUndo());
				}

				BOOST_AUTO_TEST_CASE(can_undo)
				{
					BOOST_CHECK_NO_THROW(document.Undo());
					BOOST_CHECK_EQUAL(document.GetItemsCount(), 1);
					BOOST_CHECK_EQUAL(document.GetItem(0)->GetParagraph()->GetText(), PARAGRAPH_TEXT);
				}

				BOOST_AUTO_TEST_CASE(returns_false_when_check_redo)
				{
					BOOST_CHECK(!document.CanRedo());
				}

				BOOST_AUTO_TEST_CASE(cant_redo)
				{
					BOOST_CHECK_THROW(document.Redo(), std::runtime_error);
					BOOST_CHECK_EQUAL(document.GetItemsCount(), 0);
				}

			BOOST_AUTO_TEST_SUITE_END()

			BOOST_FIXTURE_TEST_SUITE(when_delete_image_command_is_deleted_from_history, DocumentWithDeletedItemAfterUndoDeletedFromHistory)

				BOOST_AUTO_TEST_CASE(deleted_item_is_exist)
				{
					BOOST_CHECK_EQUAL(document.GetItemsCount(), 1);
					BOOST_CHECK_EQUAL(document.GetItem(0)->GetParagraph()->GetText(), PARAGRAPH_TEXT);
				}

				BOOST_AUTO_TEST_CASE(can_undo_twice)
				{
					BOOST_CHECK(document.CanUndo());
					document.Undo();

					BOOST_CHECK(document.CanUndo());
					document.Undo();

					BOOST_CHECK(!document.CanUndo());
					BOOST_CHECK_THROW(document.Undo(), std::runtime_error);
				}

				BOOST_AUTO_TEST_CASE(cant_redo)
				{
					BOOST_CHECK_THROW(document.Redo(), std::runtime_error);
				}

			BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()