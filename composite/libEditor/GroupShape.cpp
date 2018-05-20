#include "stdafx.h"
#include "GroupShape.h"

CGroupShape::CGroupShape()
	: m_fillStyle(*this), m_outlineStyle(*this)
{
}

void CGroupShape::Draw(ICanvas& canvas) const
{
	for (auto&& shape : m_shapes)
	{
		shape->Draw(canvas);
	}
}

RectD CGroupShape::GetFrame() const
{
	if (m_shapes.empty())
	{
		return { { 0, 0 }, 0, 0 };
	}

	double topY = std::numeric_limits<double>::max();
	double rightX = std::numeric_limits<double>::min();
	double bottomY = std::numeric_limits<double>::min();
	double leftX = std::numeric_limits<double>::max();

	for (auto&& shape : m_shapes)
	{
		RectD const& frame = shape->GetFrame();
		PointD const& shapeLeftTop = frame.leftTop;
		PointD const& shapeRightBottom = {shapeLeftTop.x + frame.width, shapeLeftTop.y + frame.height};

		leftX = std::min(leftX, shapeLeftTop.x);
		topY = std::min(topY, shapeLeftTop.y);
		rightX = std::max(rightX, shapeRightBottom.x);
		bottomY = std::max(bottomY, shapeRightBottom.y);
	}

	return { { leftX, topY },  rightX - leftX, bottomY - topY };
}

void CGroupShape::SetFrame(RectD const& rect)
{
	if (m_shapes.empty())
	{
		return;
	}

	const RectD currentFrame = GetFrame();
	const double frameOffsetX = rect.leftTop.x - currentFrame.leftTop.x;
	const double frameOffsetY = rect.leftTop.y - currentFrame.leftTop.y;

	const PointD leftTop = rect.leftTop;
	const double frameScaleX = rect.width / currentFrame.width;
	const double frameScaleY = rect.height / currentFrame.height;

	const auto updateShapeFrame = [&](std::shared_ptr<IShape> const& shape) {	
		RectD shapeFrame = shape->GetFrame();
		shapeFrame.leftTop.x += frameOffsetX;
		shapeFrame.leftTop.y += frameOffsetY;

		const double shapeOffsetX = shapeFrame.leftTop.x - leftTop.x;
		const double shapeOffsetY = shapeFrame.leftTop.y - leftTop.y;

		shapeFrame.leftTop.x = leftTop.x + (shapeOffsetX * frameScaleX);
		shapeFrame.leftTop.y = leftTop.y + (shapeOffsetY * frameScaleY);
		shapeFrame.width *= frameScaleX;
		shapeFrame.height *= frameScaleY;
		shape->SetFrame(shapeFrame);
	};

	boost::range::for_each(m_shapes, updateShapeFrame);
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

void CGroupShape::EnumerateFillStyles(std::function<bool(IStyle&)> func) const
{
	for (auto&& shape : m_shapes)
	{
		if (!func(shape->GetFillStyle()))
		{
			break;
		}
	}
}

void CGroupShape::EnumerateOutlineStyles(std::function<bool(IOutlineStyle&)> func) const
{
	for (auto&& shape : m_shapes)
	{
		if (!func(shape->GetOutlineStyle()))
		{
			break;
		}
	}
}