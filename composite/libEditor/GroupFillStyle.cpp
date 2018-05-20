#include "stdafx.h"
#include "GroupFillStyle.h"

CGroupFillStyle::CGroupFillStyle(IFillStyleEnumerator& enumerator)
	: m_enumerator(enumerator)
{
}

boost::optional<bool> CGroupFillStyle::IsEnabled() const
{
	boost::optional<boost::optional<bool>> firstShapeValue;
	bool isCommonValue = true;

	m_enumerator.EnumerateFillStyles([&](IStyle& style) {
		if (!firstShapeValue.is_initialized())
		{
			firstShapeValue = style.IsEnabled();
		}
		if (firstShapeValue.value() != style.IsEnabled())
		{
			isCommonValue = false;
			return false;
		}
		return true;
	});
	return (firstShapeValue.is_initialized() && isCommonValue) ? (*firstShapeValue) : boost::optional<bool>();
}

void CGroupFillStyle::Enable(bool enable)
{
	m_enumerator.EnumerateFillStyles([&](IStyle& style) {
		style.Enable(enable);
		return true;
	});
}

boost::optional<RGBAColor> CGroupFillStyle::GetColor() const
{
	boost::optional<boost::optional<RGBAColor>> firstShapeValue;
	bool isCommonValue = true;

	m_enumerator.EnumerateFillStyles([&](IStyle& style) {
		if (!firstShapeValue.is_initialized())
		{
			firstShapeValue = style.GetColor();
		}
		if (firstShapeValue.value() != style.GetColor())
		{
			isCommonValue = false;
			return false;
		}
		return true;
	});

	return (firstShapeValue.is_initialized() && isCommonValue) ? (*firstShapeValue) : boost::optional<RGBAColor>();
}

void CGroupFillStyle::SetColor(RGBAColor color)
{
	m_enumerator.EnumerateFillStyles([&](IStyle& style) {
		style.SetColor(color);
		return true;
	});
}