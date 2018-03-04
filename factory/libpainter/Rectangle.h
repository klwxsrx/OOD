#pragma once
#include "Shape.h"
#include "Point.h"
#include "ICanvas.h"

class CRectangle : public CShape
{
public:
	CRectangle(CPoint const& leftTop, CPoint const& rightBottom, Color color);
	
	CPoint GetLeftTop()const;
	CPoint GetRightBottom()const;

protected:
	void DrawImpl(ICanvas & canvas)override;

private:
	CPoint m_leftTop, m_rightBottom;
};