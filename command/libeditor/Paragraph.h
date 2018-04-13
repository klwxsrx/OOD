#pragma once
#include "IParagraph.h"

class CParagraph : public IParagraph
{
public:
	CParagraph(std::string const& paragraph);	
	std::string GetText() const override;
	void SetText(std::string const & text) override;
	void ConnectOnChange(std::function<void(std::string&, std::string const&)> callback);

private:
	std::string m_paragraph;
	boost::signals2::signal<void(std::string&, std::string const&)> m_onChange;
};

