#pragma once
#include "IDrawable.h"
#include "IStyle.h"
#include "IOutlineStyle.h"

class IGroupShape;

class IShape : public IDrawable
{
public:
	virtual RectD GetFrame() const = 0;
	virtual void SetFrame(RectD const& rect) = 0;

	virtual IOutlineStyle& GetOutlineStyle() = 0;
	virtual const IOutlineStyle& GetOutlineStyle() const = 0;

	virtual IStyle& GetFillStyle() = 0;
	virtual const IStyle& GetFillStyle() const = 0;

	virtual std::shared_ptr<IGroupShape> GetGroup() = 0;
	virtual std::shared_ptr<const IGroupShape> GetGroup() const = 0;

	virtual ~IShape() = default;
};