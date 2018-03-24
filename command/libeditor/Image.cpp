#include "stdafx.h"
#include "Image.h"

CImage::CImage(IFileResource::Ptr && resource, unsigned width, unsigned height)
	: m_resource(resource)
	, m_width(width)
	, m_height(height)
{
}

void CImage::Resize(unsigned width, unsigned height)
{
	m_width = width;
	m_height = height;
}

boost::filesystem::path CImage::GetPath()const
{
	return m_resource->GetPath();
}

unsigned CImage::GetWidth()const
{
	return m_width;
}

unsigned CImage::GetHeight()const
{
	return m_height;
}