#pragma once
#include "IDocumentItem.h"
#include "Paragraph.h"

class CParagraphDocumentItem : public IDocumentItem
{
public:
	CParagraphDocumentItem(std::string const& paragraph);
	std::string GetDescription() const override;
	std::shared_ptr<CParagraph> GetParagraph();

private:
	std::shared_ptr<CParagraph> m_paragraph;
};

