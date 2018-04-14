#include "stdafx.h"
#include "../libeditor/Document.h"
#include "../libeditor/FileUtils.h"

struct EmptyDocumentFixture
{
	CDocument document;
	const std::string DEFAULT_DOCUMENT_TITLE = "Untitled document";
	const std::string TEST_IMAGE_PATH = "test.jpg";
};
struct DocumentWithCustomTitleFixture : EmptyDocumentFixture
{
	const std::string NEW_TITLE = "NewTitle";
	DocumentWithCustomTitleFixture()
	{
		document.SetTitle(NEW_TITLE);
	}
};

struct DocumentWithCustomTitleFixtureAfterUndo : DocumentWithCustomTitleFixture
{
	DocumentWithCustomTitleFixtureAfterUndo()
	{
		document.Undo();
	}
};

struct DocumentWithCustomTitleFixtureAfterUndoDeletedFromHistory : DocumentWithCustomTitleFixtureAfterUndo
{
	DocumentWithCustomTitleFixtureAfterUndoDeletedFromHistory()
	{
		document.InsertParagraph("Test"); // execute some command to delete undo`ed command from history
	}
};

struct DocumentWithCustomTitleFixtureAfterUndoAndRedo : DocumentWithCustomTitleFixtureAfterUndo
{
	DocumentWithCustomTitleFixtureAfterUndoAndRedo()
	{
		document.Redo();
	}
};

BOOST_AUTO_TEST_SUITE(Document)

	BOOST_FIXTURE_TEST_SUITE(when_title_is_set, DocumentWithCustomTitleFixture)

		BOOST_AUTO_TEST_CASE(can_insert_paragraph)
		{
			auto paragraph = document.InsertParagraph("Test");
			BOOST_CHECK(document.GetItem(0)->GetParagraph() == paragraph);
			BOOST_CHECK_EQUAL(document.GetTitle(), NEW_TITLE);
		}

		BOOST_AUTO_TEST_CASE(can_insert_image)
		{
			auto image = document.InsertImage(TEST_IMAGE_PATH, 640u, 480u);
			BOOST_CHECK(document.GetItem(0)->GetImage() == image);
			BOOST_CHECK_EQUAL(document.GetTitle(), NEW_TITLE);
		}

		BOOST_AUTO_TEST_CASE(returns_zero_items_count)
		{
			BOOST_CHECK_EQUAL(document.GetItemsCount(), 0);
		}

		BOOST_AUTO_TEST_CASE(cant_get_item)
		{
			BOOST_CHECK_THROW(document.GetItem(0), std::runtime_error);
			BOOST_CHECK_THROW(document.GetItem(1), std::runtime_error);
			BOOST_CHECK_THROW(document.GetItem(2), std::runtime_error);
			BOOST_CHECK_EQUAL(document.GetTitle(), NEW_TITLE);
		}

		BOOST_AUTO_TEST_CASE(cant_delete_item)
		{
			BOOST_CHECK_THROW(document.DeleteItem(0), std::runtime_error);
			BOOST_CHECK_THROW(document.DeleteItem(1), std::runtime_error);
			BOOST_CHECK_THROW(document.DeleteItem(2), std::runtime_error);
			BOOST_CHECK_EQUAL(document.GetTitle(), NEW_TITLE);
			BOOST_CHECK(document.CanUndo());
		}

		BOOST_AUTO_TEST_CASE(can_set_title)
		{
			const std::string NEW_NEW_TITLE = "NewNewTitle";
			document.SetTitle(NEW_NEW_TITLE);
			BOOST_CHECK_EQUAL(document.GetTitle(), NEW_NEW_TITLE);
		}

		BOOST_AUTO_TEST_CASE(can_set_empty_title)
		{
			BOOST_CHECK_THROW(document.SetTitle(""), std::runtime_error);
		}

		BOOST_AUTO_TEST_CASE(has_custom_title)
		{
			BOOST_CHECK_EQUAL(document.GetTitle(), NEW_TITLE);
		}

		BOOST_AUTO_TEST_CASE(returns_true_when_check_can_undo)
		{
			BOOST_CHECK(document.CanUndo());
		}

		BOOST_AUTO_TEST_CASE(can_undo)
		{
			document.Undo();
			BOOST_CHECK_EQUAL(document.GetTitle(), DEFAULT_DOCUMENT_TITLE);
		}

		BOOST_AUTO_TEST_CASE(returns_false_when_check_can_redo)
		{
			BOOST_CHECK(!document.CanRedo());
		}

		BOOST_AUTO_TEST_CASE(cant_redo)
		{
			BOOST_CHECK_THROW(document.Redo(), std::runtime_error);
			BOOST_CHECK_EQUAL(document.GetTitle(), NEW_TITLE);
			BOOST_CHECK(document.CanUndo());
		}

		BOOST_FIXTURE_TEST_SUITE(after_undo, DocumentWithCustomTitleFixtureAfterUndo)

			BOOST_AUTO_TEST_CASE(can_insert_paragraph)
			{
				auto paragraph = document.InsertParagraph("Test");
				BOOST_CHECK(document.GetItem(0)->GetParagraph() == paragraph);
				BOOST_CHECK_EQUAL(document.GetTitle(), DEFAULT_DOCUMENT_TITLE);
			}

			BOOST_AUTO_TEST_CASE(can_insert_image)
			{
				auto image = document.InsertImage(TEST_IMAGE_PATH, 640u, 480u);
				BOOST_CHECK(document.GetItem(0)->GetImage() == image);
				BOOST_CHECK_EQUAL(document.GetTitle(), DEFAULT_DOCUMENT_TITLE);
			}

			BOOST_AUTO_TEST_CASE(returns_zero_items_count)
			{
				BOOST_CHECK_EQUAL(document.GetItemsCount(), 0);
			}

			BOOST_AUTO_TEST_CASE(cant_get_item)
			{
				BOOST_CHECK_THROW(document.GetItem(0), std::runtime_error);
				BOOST_CHECK_THROW(document.GetItem(1), std::runtime_error);
				BOOST_CHECK_THROW(document.GetItem(2), std::runtime_error);
				BOOST_CHECK_EQUAL(document.GetTitle(), DEFAULT_DOCUMENT_TITLE);
			}

			BOOST_AUTO_TEST_CASE(cant_delete_item)
			{
				BOOST_CHECK_THROW(document.DeleteItem(0), std::runtime_error);
				BOOST_CHECK_THROW(document.DeleteItem(1), std::runtime_error);
				BOOST_CHECK_THROW(document.DeleteItem(2), std::runtime_error);
				BOOST_CHECK_EQUAL(document.GetTitle(), DEFAULT_DOCUMENT_TITLE);
				BOOST_CHECK(document.CanRedo());
			}

			BOOST_AUTO_TEST_CASE(can_set_title)
			{
				const std::string NEW_NEW_TITLE = "NewNewTitle";
				document.SetTitle(NEW_NEW_TITLE);
				BOOST_CHECK_EQUAL(document.GetTitle(), NEW_NEW_TITLE);
			}

			BOOST_AUTO_TEST_CASE(has_default_title)
			{
				BOOST_CHECK_EQUAL(document.GetTitle(), DEFAULT_DOCUMENT_TITLE);
			}

			BOOST_AUTO_TEST_CASE(returns_false_when_check_can_undo)
			{
				BOOST_CHECK(!document.CanUndo());
			}

			BOOST_AUTO_TEST_CASE(cant_undo)
			{
				BOOST_CHECK_THROW(document.Undo(), std::runtime_error);
				BOOST_CHECK_EQUAL(document.GetTitle(), DEFAULT_DOCUMENT_TITLE);
				BOOST_CHECK(document.CanRedo());
			}

			BOOST_AUTO_TEST_CASE(returns_true_when_check_can_redo)
			{
				BOOST_CHECK(document.CanRedo());
			}

			BOOST_AUTO_TEST_CASE(can_redo)
			{
				document.Redo();
				BOOST_CHECK_EQUAL(document.GetTitle(), NEW_TITLE);
			}

			BOOST_FIXTURE_TEST_SUITE(after_redo, DocumentWithCustomTitleFixtureAfterUndoAndRedo)

				BOOST_AUTO_TEST_CASE(can_insert_paragraph)
				{
					auto paragraph = document.InsertParagraph("Test");
					BOOST_CHECK(document.GetItem(0)->GetParagraph() == paragraph);
					BOOST_CHECK_EQUAL(document.GetTitle(), NEW_TITLE);
				}

				BOOST_AUTO_TEST_CASE(can_insert_image)
				{
					auto image = document.InsertImage(TEST_IMAGE_PATH, 640u, 480u);
					BOOST_CHECK(document.GetItem(0)->GetImage() == image);
					BOOST_CHECK_EQUAL(document.GetTitle(), NEW_TITLE);
				}

				BOOST_AUTO_TEST_CASE(returns_zero_items_count)
				{
					BOOST_CHECK_EQUAL(document.GetItemsCount(), 0);
				}

				BOOST_AUTO_TEST_CASE(cant_get_item)
				{
					BOOST_CHECK_THROW(document.GetItem(0), std::runtime_error);
					BOOST_CHECK_THROW(document.GetItem(1), std::runtime_error);
					BOOST_CHECK_THROW(document.GetItem(2), std::runtime_error);
					BOOST_CHECK_EQUAL(document.GetTitle(), NEW_TITLE);
				}

				BOOST_AUTO_TEST_CASE(cant_delete_item)
				{
					BOOST_CHECK_THROW(document.DeleteItem(0), std::runtime_error);
					BOOST_CHECK_THROW(document.DeleteItem(1), std::runtime_error);
					BOOST_CHECK_THROW(document.DeleteItem(2), std::runtime_error);
					BOOST_CHECK_EQUAL(document.GetTitle(), NEW_TITLE);
					BOOST_CHECK(document.CanUndo());
				}

				BOOST_AUTO_TEST_CASE(can_set_title)
				{
					const std::string NEW_NEW_TITLE = "NewNewTitle";
					document.SetTitle(NEW_NEW_TITLE);
					BOOST_CHECK_EQUAL(document.GetTitle(), NEW_NEW_TITLE);
				}

				BOOST_AUTO_TEST_CASE(has_custom_title)
				{
					BOOST_CHECK_EQUAL(document.GetTitle(), NEW_TITLE);
				}

				BOOST_AUTO_TEST_CASE(returns_true_when_check_can_undo)
				{
					BOOST_CHECK(document.CanUndo());
				}

				BOOST_AUTO_TEST_CASE(can_undo)
				{
					document.Undo();
					BOOST_CHECK_EQUAL(document.GetTitle(), DEFAULT_DOCUMENT_TITLE);
				}

				BOOST_AUTO_TEST_CASE(returns_false_when_check_can_redo)
				{
					BOOST_CHECK(!document.CanRedo());
				}

				BOOST_AUTO_TEST_CASE(cant_redo)
				{
					BOOST_CHECK_THROW(document.Redo(), std::runtime_error);
					BOOST_CHECK_EQUAL(document.GetTitle(), NEW_TITLE);
					BOOST_CHECK(document.CanUndo());
				}

			BOOST_AUTO_TEST_SUITE_END()

			BOOST_FIXTURE_TEST_SUITE(when_set_title_is_deleted_from_history, DocumentWithCustomTitleFixtureAfterUndoDeletedFromHistory)

				BOOST_AUTO_TEST_CASE(can_insert_paragraph)
				{
					auto paragraph = document.InsertParagraph("Test");
					BOOST_CHECK(document.GetItem(1)->GetParagraph() == paragraph);
					BOOST_CHECK_EQUAL(document.GetTitle(), DEFAULT_DOCUMENT_TITLE);
				}

				BOOST_AUTO_TEST_CASE(can_insert_image)
				{
					auto image = document.InsertImage(TEST_IMAGE_PATH, 640u, 480u);
					BOOST_CHECK(document.GetItem(1)->GetImage() == image);
					BOOST_CHECK_EQUAL(document.GetTitle(), DEFAULT_DOCUMENT_TITLE);
				}

				BOOST_AUTO_TEST_CASE(has_default_title)
				{
					BOOST_CHECK_EQUAL(document.GetTitle(), DEFAULT_DOCUMENT_TITLE);
				}

				BOOST_AUTO_TEST_CASE(can_undo_only_once)
				{
					BOOST_CHECK(document.CanUndo());
					document.Undo();
					
					BOOST_CHECK(!document.CanUndo());
					BOOST_CHECK_THROW(document.Undo(), std::runtime_error);
				}

				BOOST_AUTO_TEST_CASE(cant_redo)
				{
					BOOST_CHECK_THROW(document.Redo(), std::runtime_error);
					BOOST_CHECK_EQUAL(document.GetTitle(), DEFAULT_DOCUMENT_TITLE);
					BOOST_CHECK(document.CanUndo());
				}

			BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()