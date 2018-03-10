#pragma once
#include "Shape.h"

class CEllipse : public CShape
{
public:
	CEllipse(CPoint const& center, unsigned horizontalRadius, unsigned verticalRadius, Color color);
	
	CPoint GetCenter()const;
	unsigned GetHorizontalRadius()const;
	unsigned GetVerticalRadius()const;

protected:
	void DrawImpl(ICanvas & canvas)const override;

private:
	CPoint m_center;
	unsigned m_horizontalRadius;
	unsigned m_verticalRadius;
};
