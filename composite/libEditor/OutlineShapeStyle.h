#pragma once
#include "IOutlineStyle.h"
#include "ShapeStyle.h"

class COutlineShapeStyle : public IOutlineStyle, public CShapeStyle
{
public:
	COutlineShapeStyle(bool isEnabled, RGBAColor color, double strokeWidth);

	boost::optional<double> GetStrokeWidth() const override;
	void SetStrokeWidth(double width) override;

	boost::optional<bool> IsEnabled() const override;
	void Enable(bool enable) override;
	boost::optional<RGBAColor> GetColor() const override;
	void SetColor(RGBAColor color) override;

private:
	double m_strokeWidth;
};

