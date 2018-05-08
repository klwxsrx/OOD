#pragma once
#include "graphics_lib.h"
#include "modern_graphics_lib.h"

class CCanvasAdapterViaInheritance
	: public graphics_lib::ICanvas, private modern_graphics_lib::CModernGraphicsRenderer
{
public:
	CCanvasAdapterViaInheritance(std::ostream& out);

	void MoveTo(int x, int y) override;
	void LineTo(int x, int y) override;
	void SetColor(uint32_t rgbColor) override;

private:
	static float PrepareColorValue(uint8_t value);

	modern_graphics_lib::CPoint m_currentPoint;
	modern_graphics_lib::CRGBAColor m_color;
};

