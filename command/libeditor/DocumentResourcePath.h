#pragma once

class CDocumentResourcePath
{
public:
	~CDocumentResourcePath();

	boost::filesystem::path GetTempPath() const;

private:
	mutable boost::optional<boost::filesystem::path> m_tempPath;
};