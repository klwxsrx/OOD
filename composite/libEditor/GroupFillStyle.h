#pragma once
#include "IShape.h"
#include "IFillStyleEnumerator.h"

class CGroupFillStyle : public IStyle
{
public:
	CGroupFillStyle(IFillStyleEnumerator& enumerator);

	boost::optional<bool> IsEnabled() const override;
	void Enable(bool enable) override;
	boost::optional<RGBAColor> GetColor() const override;
	void SetColor(RGBAColor color) override;

private:
	IFillStyleEnumerator& m_enumerator;
};

