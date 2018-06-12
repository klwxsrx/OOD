#include "stdafx.h"
#include "MockFileResource.h"
#include "../libeditor/ImageDocumentItem.h"
#include "../libeditor/History.h"

class CTestImageExporter : public IDocumentExporter
{
public:
	void AddParagraph(std::shared_ptr<IParagraph> const & paragraph) override
	{
	}
	void AddImage(std::shared_ptr<IImage> const & image) override
	{
		m_image = image;
	}
	std::shared_ptr<IImage> m_image;
};

struct ImageDocumentItemFixture
{
	CHistory history;
	std::shared_ptr<IImage> image;
	CImageDocumentItem item;
	CImageDocumentItem* itemPtr;
	CImageDocumentItem const* itemConstPtr;
	ImageDocumentItemFixture()
		: item(std::make_shared<CMockFileResource>(), ImageSize(640u, 480u), history), itemPtr(&item), itemConstPtr(&item)
	{
		image = item.GetImage();
	}
};

BOOST_AUTO_TEST_SUITE(ImageDocumentItem)
	
	BOOST_AUTO_TEST_CASE(returns_description_of_image)
	{
		CHistory history;
		CImageDocumentItem item(std::make_shared<CMockFileResource>(), ImageSize(640u, 480u), history);
		BOOST_CHECK_EQUAL(item.GetDescription(), "Image: 640 480 \"" + CMockFileResource::PATH + "\"");
	}
	
	BOOST_FIXTURE_TEST_CASE(returns_image, ImageDocumentItemFixture)
	{
		BOOST_CHECK(itemPtr->GetImage() == image);
		BOOST_CHECK(itemConstPtr->GetImage() == image);
	}

	BOOST_FIXTURE_TEST_CASE(returns_empty_paragrap_ptr, ImageDocumentItemFixture)
	{
		BOOST_CHECK(itemPtr->GetParagraph() == nullptr);
		BOOST_CHECK(itemConstPtr->GetParagraph() == nullptr);
	}

	BOOST_FIXTURE_TEST_CASE(returns_image_to_exporter, ImageDocumentItemFixture)
	{
		std::unique_ptr<CTestImageExporter> exporter = std::make_unique<CTestImageExporter>();
		item.AcceptExporter(exporter.get());

		BOOST_CHECK(exporter->m_image == image);
	}

BOOST_AUTO_TEST_SUITE_END()