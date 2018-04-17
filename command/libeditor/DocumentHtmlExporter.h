#pragma once
#include "IDocumentExporter.h"
#include "Document.h"

class CDocumentHtmlExporter : public IDocumentExporter
{
public:
	CDocumentHtmlExporter(CDocument const& document, boost::filesystem::path const& pathToHtmlFile);

	void AddParagraph(std::shared_ptr<IParagraph> const& paragraph) override;
	void AddImage(std::shared_ptr<IImage> const& image) override;
	void Export();

private:
	void OpenFileForSave(std::string const& path);
	void WriteDocumentHeader(CDocument const& document);
	boost::filesystem::path CopyImageResource(boost::filesystem::path const& source);
	static boost::filesystem::path CreateResultFileResourcesPath(boost::filesystem::path const& filePath);
	static std::string EncodeString(std::string const& str);

	boost::filesystem::path m_resultFilePath;
	boost::optional<boost::filesystem::path> m_resultFileResourcesPath;

	std::vector<boost::filesystem::path> m_resources;
	std::ofstream m_resultFile;
	std::stringstream m_htmlResult;
};