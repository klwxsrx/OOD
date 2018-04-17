#pragma once
#include "DocumentItem.h"
#include "Image.h"

class CImageDocumentItem : public CDocumentItem
{
public:
	CImageDocumentItem(IFileResource::Ptr && resource, unsigned width, unsigned height);
	CImageDocumentItem(std::shared_ptr<CImage> const& image);
	CImageDocumentItem(std::shared_ptr<CImage> && image);
	~CImageDocumentItem() = default;
	std::string GetDescription()const override;
	std::shared_ptr<IImage> GetImage() override;
	std::shared_ptr<const IImage> GetImage() const override;
	void AcceptExporter(std::shared_ptr<IDocumentExporter>& exporter) const override;

private:
	std::shared_ptr<CImage> m_image;
};