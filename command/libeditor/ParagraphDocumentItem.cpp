#include "stdafx.h"
#include "ParagraphDocumentItem.h"


CParagraphDocumentItem::CParagraphDocumentItem(std::string const& paragraph)
	: m_paragraph(paragraph)
{
}

std::string CParagraphDocumentItem::GetDescription() const
{
	return (boost::format("Paragraph: %1%") % m_paragraph.GetText()).str();
}