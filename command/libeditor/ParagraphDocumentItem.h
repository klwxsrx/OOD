#pragma once
#include "DocumentItem.h"
#include "Paragraph.h"

class CParagraphDocumentItem : public CDocumentItem
{
public:
	CParagraphDocumentItem(std::string const& paragraph);
	CParagraphDocumentItem(std::shared_ptr<IParagraph> && paragraph);
	~CParagraphDocumentItem() = default;
	std::string GetDescription() const override;
	std::shared_ptr<IParagraph> GetParagraph() override;
	std::shared_ptr<const IParagraph> GetParagraph() const override;
	void AcceptExporter(std::shared_ptr<IDocumentExporter>& exporter) const override;

private:
	std::shared_ptr<IParagraph> m_paragraph;
};

