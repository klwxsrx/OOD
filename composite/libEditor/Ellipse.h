#pragma once
#include "Shape.h"

class CEllipse : public CShape
{
public:
	CEllipse(PointD const& center, double horizontalRadius, double verticalRadius);

	void DrawImpl(ICanvas& canvas) const override;
	RectD GetFrame() override;
	void SetFrame(RectD const& rect) override;

private:
	PointD m_center;
	double m_horizontalRadius, m_verticalRadius;
};

