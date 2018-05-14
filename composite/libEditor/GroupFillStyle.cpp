#include "stdafx.h"
#include "GroupFillStyle.h"

CGroupFillStyle::CGroupFillStyle(std::list<std::shared_ptr<IShape>>& shapes)
	: m_shapes(shapes)
{
}

boost::optional<bool> CGroupFillStyle::IsEnabled() const
{
	if (m_shapes.empty())
	{
		return boost::optional<bool>();
	}

	boost::optional<bool> firstShapeValue = m_shapes.front()->GetFillStyle().IsEnabled();
	bool isCommonValue = std::all_of(m_shapes.begin(), m_shapes.end(), [&firstShapeValue](std::shared_ptr<IShape> const& shape) {
		return shape->GetFillStyle().IsEnabled() == firstShapeValue;
	});

	return isCommonValue ? firstShapeValue : boost::optional<bool>();
}

void CGroupFillStyle::Enable(bool enable)
{
	for (std::shared_ptr<IShape> const& shape : m_shapes)
	{
		shape->GetFillStyle().Enable(enable);
	}
}

boost::optional<RGBAColor> CGroupFillStyle::GetColor() const
{
	if (m_shapes.empty())
	{
		return boost::optional<RGBAColor>();
	}

	boost::optional<RGBAColor> firstShapeValue = m_shapes.front()->GetFillStyle().GetColor();
	bool isCommonValue = std::all_of(m_shapes.begin(), m_shapes.end(), [&firstShapeValue](std::shared_ptr<IShape> const& shape) {
		return shape->GetFillStyle().GetColor() == firstShapeValue;
	});

	return isCommonValue ? firstShapeValue : boost::optional<RGBAColor>();
}

void CGroupFillStyle::SetColor(RGBAColor color)
{
	for (std::shared_ptr<IShape> const& shape : m_shapes)
	{
		shape->GetFillStyle().SetColor(color);
	}
}