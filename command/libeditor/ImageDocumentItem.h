#pragma once
#include "IDocumentItem.h"
#include "Image.h"

class CImageDocumentItem : public IDocumentItem
{
public:
	CImageDocumentItem(IFileResource::Ptr && resource, unsigned width, unsigned height);
	std::string GetDescription()const override;

private:
	CImage m_image;
};