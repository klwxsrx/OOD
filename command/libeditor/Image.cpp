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

bool CImage::operator==(CImage const& other) const
{
	return m_resource->GetPath() == other.m_resource->GetPath()
		&& m_size.height == other.m_size.height
		&& m_size.width == other.m_size.width;
}