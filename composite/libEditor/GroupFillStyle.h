#pragma once
#include "IShape.h"

class CGroupFillStyle : public IStyle
{
public:
	CGroupFillStyle(std::list<std::shared_ptr<IShape>>& shapes);

	boost::optional<bool> IsEnabled() const override;
	void Enable(bool enable) override;
	boost::optional<RGBAColor> GetColor() const override;
	void SetColor(RGBAColor color) override;

private:
	std::list<std::shared_ptr<IShape>>& m_shapes;
};

