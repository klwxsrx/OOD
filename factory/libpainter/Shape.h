#pragma once
#include "ICanvas.h"
#include "Color.h"

class CShape
{
public:
	CShape(Color color);
	virtual ~CShape() = default;
	
	void Draw(ICanvas & canvas);
	Color GetColor()const;

protected:
	virtual void DrawImpl(ICanvas &) {};

private:
	Color m_color;
};