#pragma once

class CDocumentResourcePath
{
public:
	~CDocumentResourcePath();

	boost::filesystem::path GetTempPath();

private:
	boost::optional<boost::filesystem::path> m_tempPath;
};