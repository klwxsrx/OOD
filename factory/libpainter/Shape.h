#pragma once
#include "ICanvas.h"
#include "Color.h"

class CShape
{
public:
	CShape(Color color);
	virtual ~CShape();
	
	void Draw(ICanvas & canvas);
	Color GetColor()const;

private:
	Color m_color;
};

