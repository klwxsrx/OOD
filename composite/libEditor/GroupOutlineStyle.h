#pragma once
#include "IShape.h"
#include "IOutlineStyleEnumerator.h"

class CGroupOutlineStyle : public IOutlineStyle
{
public:
	CGroupOutlineStyle(IOutlineStyleEnumerator& enumerator);

	boost::optional<bool> IsEnabled() const override;
	void Enable(bool enable) override;
	boost::optional<RGBAColor> GetColor() const override;
	void SetColor(RGBAColor color) override;
	boost::optional<double> GetStrokeWidth() const override;
	void SetStrokeWidth(double width) override;

private:
	IOutlineStyleEnumerator& m_enumerator;
};

