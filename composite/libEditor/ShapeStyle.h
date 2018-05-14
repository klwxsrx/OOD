#pragma once
#include "IStyle.h"

class CShapeStyle : public IStyle
{
public:
	CShapeStyle(bool isEnabled, RGBAColor color);
	boost::optional<bool> IsEnabled() const override;
	void Enable(bool enable) override;

	boost::optional<RGBAColor> GetColor() const override;
	void SetColor(RGBAColor color) override;

	virtual ~CShapeStyle() = default;

private:
	boost::optional<bool> m_isEnabled;
	boost::optional<RGBAColor> m_color;
};

