#pragma once
#include "IShape.h"
#include "OutlineShapeStyle.h"

class CShape : public IShape
{
public:
	CShape();

	void Draw(ICanvas& canvas) const override;

	IOutlineStyle& GetOutlineStyle() override;
	const IOutlineStyle& GetOutlineStyle() const override;

	IStyle& GetFillStyle() override;
	const IStyle& GetFillStyle() const override;

	std::shared_ptr<IGroupShape> GetGroup() override;
	std::shared_ptr<const IGroupShape> GetGroup() const override;

	virtual void DrawImpl(ICanvas& canvas) const = 0;
	virtual ~CShape() = default;

private:
	COutlineShapeStyle m_outlineStyle;
	CShapeStyle m_fillStyle;
};

