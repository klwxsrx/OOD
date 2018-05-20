#pragma once
#include "ISlide.h"
#include "GroupShape.h"

class CSlide : public ISlide
{
public:
	void Draw(ICanvas& canvas) const override;
	double GetWidth() const override;
	double GetHeight() const override;
	IShapes& GetShapes() override;

private:
	CGroupShape m_shapeGroup;
};

