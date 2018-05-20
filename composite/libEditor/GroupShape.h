#pragma once
#include "IGroupShape.h"
#include "IFillStyleEnumerator.h"
#include "IOutlineStyleEnumerator.h"
#include "GroupFillStyle.h"
#include "GroupOutlineStyle.h"

class CGroupShape :	public IGroupShape, private IFillStyleEnumerator, private IOutlineStyleEnumerator, public std::enable_shared_from_this<CGroupShape>
{
public:
	CGroupShape();

	void Draw(ICanvas& canvas) const override;

	RectD GetFrame() const override;
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
	void EnumerateFillStyles(std::function<bool(IStyle&)> func) const override;
	void EnumerateOutlineStyles(std::function<bool(IOutlineStyle&)> func) const override;

	std::vector<std::shared_ptr<IShape>> m_shapes;
	CGroupOutlineStyle m_outlineStyle;
	CGroupFillStyle m_fillStyle;
};

