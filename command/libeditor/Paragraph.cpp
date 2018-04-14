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

void CParagraph::SetText(std::string const& text)
{
	if (m_paragraph != text)
	{
		m_onChange(m_paragraph, text);
	}
}

void CParagraph::ConnectOnChange(std::function<void(std::string&, std::string const&)> callback)
{
	m_onChange.connect(callback);
}

bool CParagraph::operator==(CParagraph const& other) const
{
	return m_paragraph == other.m_paragraph;
}