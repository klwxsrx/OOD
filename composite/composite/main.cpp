#include "stdafx.h"
#include "../libEditor/SvgCanvas.h"
#include "../libEditor/Triangle.h"
#include "../libEditor/Ellipse.h"

int main()
{
	CSvgCanvas canvas;
	CTriangle triangle = CTriangle({ 100, 100 }, { 100, 200 }, { 300, 300 });
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

