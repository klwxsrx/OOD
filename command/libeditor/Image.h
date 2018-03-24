#pragma once
#include "IIMage.h"
#include "IDocumentItem.h"
#include "FileResource.h"

class CImage : public IImage
{
public:
	CImage(IFileResource::Ptr && resource, unsigned width, unsigned height);

	void Resize(unsigned width, unsigned height) override;
	boost::filesystem::path GetPath()const override;
	unsigned GetWidth()const override;
	unsigned GetHeight()const override;

private:
	unsigned m_width = 0;
	unsigned m_height = 0;
	IFileResource::Ptr m_resource;
};