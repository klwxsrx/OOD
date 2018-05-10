#pragma once
#include "Shape.h"

class CRectangle : public CShape
{
public:
	CRectangle(PointD leftTop, double width, double height);

	void DrawImpl(ICanvas& canvas) const override;
	RectD GetFrame() override;
	void SetFrame(RectD const& rect) override;

private:
	PointD m_leftTop;
	double m_width, m_height;
};

