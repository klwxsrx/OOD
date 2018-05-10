#pragma once
#include "IShape.h"
#include "ShapeStyle.h"

class CShape : public IShape
{
public:
	CShape();

	void Draw(ICanvas& canvas) const override;

	IStyle& GetOutlineStyle() override;
	const IStyle& GetOutlineStyle() const override;

	IStyle& GetFillStyle() override;
	const IStyle& GetFillStyle() const override;

	std::shared_ptr<IGroupShape> GetGroup() override;
	std::shared_ptr<const IGroupShape> GetGroup() const override;

	virtual void DrawImpl(ICanvas& canvas) const = 0;
	virtual ~CShape() = default;

private:
	CShapeStyle m_outlineStyle, m_fillStyle;
};

