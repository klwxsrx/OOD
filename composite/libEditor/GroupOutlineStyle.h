#pragma once
#include "IShape.h"

class CGroupOutlineStyle : public IOutlineStyle
{
public:
	CGroupOutlineStyle(std::list<std::shared_ptr<IShape>>& shapes);

	boost::optional<bool> IsEnabled() const override;
	void Enable(bool enable) override;
	boost::optional<RGBAColor> GetColor() const override;
	void SetColor(RGBAColor color) override;
	boost::optional<double> GetStrokeWidth() const override;
	void SetStrokeWidth(double width) override;

private:
	std::list<std::shared_ptr<IShape>>& m_shapes;
};

