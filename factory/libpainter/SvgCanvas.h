#pragma once
#include "ICanvas.h"

class CSvgCanvas final : public ICanvas
{
public:
	void SetColor(Color color)override;
	void DrawLine(CPoint const& from, CPoint const& to)override;
	void DrawEclipse(CPoint const& center, unsigned horizontalRadius, unsigned verticalRadius)override;

	std::string GetResult() const;
private:
	std::stringstream m_canvas;
	RgbColor m_currentColor;
};
