#include "stdafx.h"
#include "Image.h"

CImage::CImage(IFileResource::Ptr && resource, unsigned width, unsigned height)
	: m_resource(resource)
	, m_size(width, height)
{
}

void CImage::Resize(unsigned width, unsigned height)
{
	m_onResize(m_size, ImageSize(width, height));
}

boost::filesystem::path CImage::GetPath()const
{
	return m_resource->GetPath();
}

unsigned CImage::GetWidth()const
{
	return m_size.width;
}

unsigned CImage::GetHeight()const
{
	return m_size.height;
}

void CImage::ConnectOnResize(std::function<void(ImageSize&, ImageSize const&)> callback)
{
	m_onResize.connect(callback);
}