#pragma once
#include "IShape.h"
#include "ICanvas.h"

class CShape : public IShape
{
public:
	CShape(Color color);
	
	void Draw(ICanvas & canvas)const override;
	Color GetColor()const;

protected:
	virtual void DrawImpl(ICanvas &)const {};

private:
	Color m_color;
};