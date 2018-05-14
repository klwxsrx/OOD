#include "stdafx.h"
#include "../libEditor/SvgCanvas.h"
#include "../libEditor/Triangle.h"
#include "../libEditor/Ellipse.h"

int main()
{
	CSvgCanvas canvas;
	CTriangle triangle = CTriangle({ 100, 100 }, { 100, 200 }, { 300, 300 });
	triangle.GetFillStyle().SetColor(0x0000FFFF);
	triangle.GetFillStyle().Enable(true);
	triangle.GetOutlineStyle().SetColor(0x00FFFFFF);
	triangle.GetOutlineStyle().Enable(true);
	CEllipse ellipse = CEllipse({ 300, 300 }, 200, 150);
	ellipse.GetFillStyle().SetColor(0xFF0000FF);
	ellipse.GetFillStyle().Enable(true);
	ellipse.GetOutlineStyle().SetColor(0x00FF00FF);
	ellipse.GetOutlineStyle().Enable(true);

	triangle.Draw(canvas);
	ellipse.Draw(canvas);

	std::cout << canvas.GetResult() << std::endl;
    return 0;
}

