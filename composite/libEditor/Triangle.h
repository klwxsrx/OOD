#pragma once
#include "Shape.h"

class CTriangle : public CShape
{
public:
	CTriangle(PointD vertex1, PointD vertex2, PointD vertex3);

	RectD GetFrame() override;
	void SetFrame(RectD const& rect) override;

protected:
	void DrawImpl(ICanvas& canvas) const override;

private:
	PointD m_vertex1, m_vertex2, m_vertex3;
};

