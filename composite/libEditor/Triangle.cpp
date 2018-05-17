#include "stdafx.h"
#include "Triangle.h"

CTriangle::CTriangle(PointD vertex1, PointD vertex2, PointD vertex3)
	: m_vertex1(vertex1), m_vertex2(vertex2), m_vertex3(vertex3)
{
}

void CTriangle::DrawImpl(ICanvas& canvas) const
{
	canvas.MoveTo(m_vertex1);
	canvas.LineTo(m_vertex2);
	canvas.LineTo(m_vertex3);
	canvas.LineTo(m_vertex1);
}

RectD CTriangle::GetFrame()
{
	const std::pair<PointD, PointD> horizontalBounds = std::minmax({ m_vertex1, m_vertex2, m_vertex3 }, [](PointD const& vertex1, PointD const& vertex2) {
		return vertex1.x < vertex2.x;
	});
	const std::pair<PointD, PointD> verticalBounds = std::minmax({ m_vertex1, m_vertex2, m_vertex3 }, [](PointD const& vertex1, PointD const& vertex2) {
		return vertex1.y < vertex2.y;
	});

	const PointD leftTop = { horizontalBounds.first.x, verticalBounds.first.y };
	const double width = horizontalBounds.second.x - horizontalBounds.first.x;
	const double height = verticalBounds.second.y - verticalBounds.first.y;

	return  { leftTop, width, height };
}

void CTriangle::SetFrame(RectD const& rect)
{
	const RectD currentFrame = GetFrame();

	const double horizontalOffset = rect.leftTop.x - currentFrame.leftTop.x;
	const double verticalOffset = rect.leftTop.y - currentFrame.leftTop.y;

	const double horizontalScale = rect.width / currentFrame.width;
	const double verticalScale = rect.height / currentFrame.height;

	auto updatePointPosition = [&](PointD& point) { 
		point.x += horizontalOffset;
		point.y += verticalOffset;

		const double relativeXCoordinate = point.x - rect.leftTop.x;
		const double relativeYCoordinate = point.y - rect.leftTop.y;

		point.x = relativeXCoordinate * horizontalScale + rect.leftTop.x;
		point.y = relativeYCoordinate * verticalScale + rect.leftTop.y;
	};

	updatePointPosition(m_vertex1);
	updatePointPosition(m_vertex2);
	updatePointPosition(m_vertex3);
}
