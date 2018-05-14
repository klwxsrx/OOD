#include "stdafx.h"
#include "GroupOutlineStyle.h"

CGroupOutlineStyle::CGroupOutlineStyle(std::list<std::shared_ptr<IShape>>& shapes)
	: m_shapes(shapes)
{
}


boost::optional<bool> CGroupOutlineStyle::IsEnabled() const
{
	if (m_shapes.empty())
	{
		return boost::optional<bool>();
	}

	boost::optional<bool> firstShapeValue = m_shapes.front()->GetOutlineStyle().IsEnabled();
	bool isCommonValue = std::all_of(m_shapes.begin(), m_shapes.end(), [&firstShapeValue](std::shared_ptr<IShape> const& shape) {
		return shape->GetOutlineStyle().IsEnabled() == firstShapeValue;
	});

	return isCommonValue ? firstShapeValue : boost::optional<bool>();
}

void CGroupOutlineStyle::Enable(bool enable)
{
	for (std::shared_ptr<IShape> const& shape : m_shapes)
	{
		shape->GetOutlineStyle().Enable(enable);
	}
}

boost::optional<RGBAColor> CGroupOutlineStyle::GetColor() const
{
	if (m_shapes.empty())
	{
		return boost::optional<RGBAColor>();
	}

	boost::optional<RGBAColor> firstShapeValue = m_shapes.front()->GetOutlineStyle().GetColor();
	bool isCommonValue = std::all_of(m_shapes.begin(), m_shapes.end(), [&firstShapeValue](std::shared_ptr<IShape> const& shape) {
		return shape->GetOutlineStyle().GetColor() == firstShapeValue;
	});

	return isCommonValue ? firstShapeValue : boost::optional<RGBAColor>();
}

void CGroupOutlineStyle::SetColor(RGBAColor color)
{
	for (std::shared_ptr<IShape> const& shape : m_shapes)
	{
		shape->GetOutlineStyle().SetColor(color);
	}
}

boost::optional<double> CGroupOutlineStyle::GetStrokeWidth() const
{
	if (m_shapes.empty())
	{
		return boost::optional<double>();
	}

	boost::optional<double> firstShapeValue = m_shapes.front()->GetOutlineStyle().GetStrokeWidth();
	bool isCommonValue = std::all_of(m_shapes.begin(), m_shapes.end(), [&firstShapeValue](std::shared_ptr<IShape> const& shape) {
		return shape->GetOutlineStyle().GetStrokeWidth() == firstShapeValue;
	});

	return isCommonValue ? firstShapeValue : boost::optional<double>();
}

void CGroupOutlineStyle::SetStrokeWidth(double width)
{
	for (std::shared_ptr<IShape> const& shape : m_shapes)
	{
		shape->GetOutlineStyle().SetStrokeWidth(width);
	}
}