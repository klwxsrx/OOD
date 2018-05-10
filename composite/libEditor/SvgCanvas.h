#pragma once
#include "ICanvas.h"

class CSvgCanvas : public ICanvas
{
public:
	void SetLineColor(RGBAColor color) override;
	void BeginFill(RGBAColor color) override;
	void EndFill() override;
	void MoveTo(PointD const& point) override;
	void LineTo(PointD const& point) override;
	void DrawEllipse(PointD const& center, double horizontalRadius, double verticalRadius) override;

	std::string GetResult() const;

private:
	void DrawFill();

	bool m_fillEnabled = false;
	std::vector<PointD> m_currentPolyline;
	PointD m_currentPoint;
	std::stringstream m_canvas;
	RGBAColor m_currentFillColor = Color::TRANSPARENT_COLOR;
	RGBAColor m_currentOutlineColor = Color::TRANSPARENT_COLOR;
};

