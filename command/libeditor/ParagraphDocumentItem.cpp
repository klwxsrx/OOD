#include "stdafx.h"
#include "ParagraphDocumentItem.h"


CParagraphDocumentItem::CParagraphDocumentItem(std::string const& paragraph)
	: m_paragraph(std::make_shared<CParagraph>(paragraph))
{
}

std::string CParagraphDocumentItem::GetDescription() const
{
	return (boost::format("Paragraph: %1%") % m_paragraph->GetText()).str();
}

std::shared_ptr<CParagraph> CParagraphDocumentItem::GetParagraph()
{
	return m_paragraph;
}