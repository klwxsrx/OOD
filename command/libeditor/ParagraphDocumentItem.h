#pragma once
#include "IDocumentItem.h"
#include "Paragraph.h"

class CParagraphDocumentItem : public IDocumentItem
{
public:
	CParagraphDocumentItem(std::string const& paragraph);
	std::string GetDescription() const override;

private:
	CParagraph m_paragraph;
};

