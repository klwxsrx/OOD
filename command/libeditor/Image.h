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
	void ConnectOnResize(std::function<void(ImageSize&, ImageSize const&)> callback);

private:
	ImageSize m_size;
	IFileResource::Ptr m_resource;
	boost::signals2::signal<void(ImageSize&, ImageSize const&)> m_onResize;
};