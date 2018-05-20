#pragma once
#include "Shape.h"

class CRectangle : public CShape
{
public:
	CRectangle(PointD leftTop, double width, double height);

	RectD GetFrame() const override;
	void SetFrame(RectD const& rect) override;

protected:
	void DrawImpl(ICanvas& canvas) const override;

private:
	PointD m_leftTop;
	double m_width, m_height;
};

