#include "stdafx.h"
#include "Paragraph.h"


CParagraph::CParagraph(std::string const& paragraph)
	: m_paragraph(paragraph)
{
}

std::string CParagraph::GetText() const
{
	return m_paragraph;
}

void CParagraph::SetText(std::string const & text)
{
	m_paragraph = text;
}
