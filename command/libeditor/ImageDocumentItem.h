#pragma once
#include "IDocumentItem.h"
#include "Image.h"

class CImageDocumentItem : public IDocumentItem
{
public:
	CImageDocumentItem(IFileResource::Ptr && resource, unsigned width, unsigned height);
	std::string GetDescription()const override;
	std::shared_ptr<CImage> GetImage();

private:
	std::shared_ptr<CImage> m_image;
};