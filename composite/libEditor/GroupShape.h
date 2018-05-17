#pragma once
#include "IGroupShape.h"
#include "GroupFillStyle.h"
#include "GroupOutlineStyle.h"

class CGroupShape :	public IGroupShape, public std::enable_shared_from_this<CGroupShape>
{
public:
	CGroupShape();

	void Draw(ICanvas& canvas) const override;

	RectD GetFrame() override;
	void SetFrame(RectD const& rect) override;

	IOutlineStyle& GetOutlineStyle() override;
	const IOutlineStyle& GetOutlineStyle() const override;

	IStyle& GetFillStyle() override;
	const IStyle& GetFillStyle() const override;

	std::shared_ptr<IGroupShape> GetGroup() override;
	std::shared_ptr<const IGroupShape> GetGroup() const override;

	size_t GetShapesCount() const override;
	void InsertShape(std::shared_ptr<IShape> const& shape, boost::optional<size_t> position = boost::none) override;
	std::shared_ptr<IShape> GetShapeAtIndex(size_t index) override;
	void RemoveShapeAtIndex(size_t index) override;

private:
	void ValidateItemPosition(size_t index);

	std::list<std::shared_ptr<IShape>> m_shapes;
	CGroupOutlineStyle m_outlineStyle;
	CGroupFillStyle m_fillStyle;
};

