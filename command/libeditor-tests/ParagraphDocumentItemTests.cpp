#include "stdafx.h"
#include "../libeditor/ParagraphDocumentItem.h"
#include "../libeditor/IDocumentExporter.h"

class CTestParagraphExporter : public IDocumentExporter
{
public:
	void AddParagraph(std::shared_ptr<IParagraph> const & paragraph) override
	{
		m_paragraph = paragraph;
	}
	void AddImage(std::shared_ptr<IImage> const & image) override
	{
	}
	std::shared_ptr<IParagraph> m_paragraph;
};

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

	BOOST_FIXTURE_TEST_CASE(returns_paragraph_to_exporter, ParagraphDocumentItemFixture)
	{
		std::shared_ptr<IDocumentExporter> exporter = std::make_unique<CTestParagraphExporter>();
		item.AcceptExporter(exporter);

		CTestParagraphExporter* testExporterPtr = static_cast<CTestParagraphExporter*>(exporter.get());
		BOOST_CHECK(testExporterPtr->m_paragraph == paragraph);
	}

BOOST_AUTO_TEST_SUITE_END()