#include "stdafx.h"
#include "GroupOutlineStyle.h"

CGroupOutlineStyle::CGroupOutlineStyle(IOutlineStyleEnumerator& enumerator)
	: m_enumerator(enumerator)
{
}


boost::optional<bool> CGroupOutlineStyle::IsEnabled() const
{
	boost::optional<boost::optional<bool>> firstShapeValue;
	bool isCommonValue = true;

	m_enumerator.EnumerateOutlineStyles([&](IOutlineStyle& style) {
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

void CGroupOutlineStyle::Enable(bool enable)
{
	m_enumerator.EnumerateOutlineStyles([&](IOutlineStyle& style) {
		style.Enable(enable);
		return true;
	});
}

boost::optional<RGBAColor> CGroupOutlineStyle::GetColor() const
{
	boost::optional<boost::optional<RGBAColor>> firstShapeValue;
	bool isCommonValue = true;

	m_enumerator.EnumerateOutlineStyles([&](IOutlineStyle& style) {
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

void CGroupOutlineStyle::SetColor(RGBAColor color)
{
	m_enumerator.EnumerateOutlineStyles([&](IOutlineStyle& style) {
		style.SetColor(color);
		return true;
	});
}

boost::optional<double> CGroupOutlineStyle::GetStrokeWidth() const
{
	boost::optional<boost::optional<double>> firstShapeValue;
	bool isCommonValue = true;

	m_enumerator.EnumerateOutlineStyles([&](IOutlineStyle& style) {
		if (!firstShapeValue.is_initialized())
		{
			firstShapeValue = style.GetStrokeWidth();
		}
		if (firstShapeValue.value() != style.GetStrokeWidth())
		{
			isCommonValue = false;
			return false;
		}
		return true;
	});

	return (firstShapeValue.is_initialized() && isCommonValue) ? (*firstShapeValue) : boost::optional<double>();
}

void CGroupOutlineStyle::SetStrokeWidth(double width)
{
	m_enumerator.EnumerateOutlineStyles([&](IOutlineStyle& style) {
		style.SetStrokeWidth(width);
		return true;
	});
}