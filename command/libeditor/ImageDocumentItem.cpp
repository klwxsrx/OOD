#include "stdafx.h"
#include "ImageDocumentItem.h"


CImageDocumentItem::CImageDocumentItem(IFileResource::Ptr && resource, unsigned width, unsigned height)
	: m_image(std::make_shared<CImage>(std::move(resource), width, height))
{
}

std::string CImageDocumentItem::GetDescription()const
{
	return (boost::format("Image: %1% %2% %3%") % m_image->GetWidth() % m_image->GetHeight() % m_image->GetPath()).str();
}

std::shared_ptr<CImage> CImageDocumentItem::GetImage()
{
	return m_image;
}