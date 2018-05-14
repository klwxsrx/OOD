#include "stdafx.h"
#include "GroupShape.h"

CGroupShape::CGroupShape()
	: m_fillStyle(m_shapes), m_outlineStyle(m_shapes)
{
}

void CGroupShape::Draw(ICanvas& canvas) const
{
	for (std::shared_ptr<IShape> const& shape : m_shapes)
	{
		shape->Draw(canvas);
	}
}

RectD CGroupShape::GetFrame()
{
	if (m_shapes.empty())
	{
		return { { 0, 0 }, 0, 0 };
	}

	double topY = std::numeric_limits<double>::max();
	double rightX = std::numeric_limits<double>::min();
	double bottomY = std::numeric_limits<double>::min();
	double leftX = std::numeric_limits<double>::max();

	for (std::shared_ptr<IShape> const& shape : m_shapes)
	{
		RectD const& frame = shape->GetFrame();
		PointD const& shapeLeftTop = frame.leftTop;
		PointD const& shapeRightBottom = {shapeLeftTop.x + frame.width, shapeLeftTop.y + frame.height};

		if (shapeLeftTop.x < leftX)
		{
			leftX = shapeLeftTop.x;
		}

		if (shapeLeftTop.y < topY)
		{
			 topY = shapeLeftTop.y;
		}

		if (shapeRightBottom.x > rightX)
		{
			rightX = shapeRightBottom.x;
		}

		if (shapeRightBottom.y > bottomY)
		{
			bottomY = shapeRightBottom.y;
		}
	}

	return { { leftX, topY },  rightX - leftX, bottomY - topY };
}

void CGroupShape::SetFrame(RectD const& rect)
{
	// TODO
}

IOutlineStyle& CGroupShape::GetOutlineStyle()
{
	return m_outlineStyle;
}

const IOutlineStyle& CGroupShape::GetOutlineStyle() const
{
	return m_outlineStyle;
}

IStyle& CGroupShape::GetFillStyle()
{
	return m_fillStyle;
}

const IStyle& CGroupShape::GetFillStyle() const
{
	return m_fillStyle;
}

std::shared_ptr<IGroupShape> CGroupShape::GetGroup()
{
	return shared_from_this();
}

std::shared_ptr<const IGroupShape> CGroupShape::GetGroup() const
{
	return shared_from_this();
}

size_t CGroupShape::GetShapesCount() const
{
	return m_shapes.size();
}

void CGroupShape::InsertShape(std::shared_ptr<IShape> const& shape, boost::optional<size_t> position)
{
	if (this == shape.get())
	{
		throw std::runtime_error("Can't add itself as a shape!");
	}

	const size_t containerSize = m_shapes.size();
	if (position == boost::none || containerSize == (*position))
	{
		m_shapes.push_back(shape);
	}
	else if (containerSize > (*position))
	{
		auto it = m_shapes.begin();
		std::advance(it, (*position));
		m_shapes.insert(it, shape);
	}
	else
	{
		throw std::runtime_error("Index out of range!");
	}
}

std::shared_ptr<IShape> CGroupShape::GetShapeAtIndex(size_t index)
{
	ValidateItemPosition(index);

	auto it = m_shapes.begin();
	std::advance(it, index);
	return *it;
}

void CGroupShape::RemoveShapeAtIndex(size_t index)
{
	ValidateItemPosition(index);

	auto it = m_shapes.begin();
	std::advance(it, index);
	m_shapes.erase(it);
}

void CGroupShape::ValidateItemPosition(size_t index)
{
	const size_t containerSize = m_shapes.size();
	if (index >= containerSize)
	{
		throw std::runtime_error("Index out of range!");
	}
}