#pragma once
#include "Shape.h"

class CEllipse : public CShape
{
public:
	CEllipse(PointD const& center, double horizontalRadius, double verticalRadius);

	RectD GetFrame() const override;
	void SetFrame(RectD const& rect) override;

protected:
	void DrawImpl(ICanvas& canvas) const override;

private:
	PointD m_center;
	double m_horizontalRadius, m_verticalRadius;
};

