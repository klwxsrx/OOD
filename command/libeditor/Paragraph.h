#pragma once
#include "IParagraph.h"

class CParagraph : public IParagraph
{
public:
	CParagraph(std::string const& paragraph);
	
	std::string GetText() const override;
	void SetText(std::string const & text) override;

private:
	std::string m_paragraph;
};

