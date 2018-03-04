#include "stdafx.h"
//#include "../libpainter/Designer.h"
#include "../libpainter/SvgCanvas.h"
#include "../libpainter/Rectangle.h"
#include "../libpainter/Triangle.h"
#include "../libpainter/Ellipse.h"
#include "../libpainter/RegularPolygon.h"

using namespace std;

int main()
{

	//CDesigner designer;
	
	CRectangle rect(CPoint(0, 0), CPoint(400, 400), Color::Black);
	CTriangle triangle(CPoint(0, 0), CPoint(400, 0), CPoint(0, 400), Color::Blue);
	CTriangle triangle1(CPoint(0, 0), CPoint(400, 0), CPoint(400, 400), Color::Green);
	CEllipse ellipse(CPoint(200, 200), 150, 50, Color::Yellow);
	CRegularPolygon polygon(CPoint(200, 200), 100, 24, Color::Pink);

	CSvgCanvas canvas;

	rect.Draw(canvas);
	triangle.Draw(canvas);
	triangle1.Draw(canvas);
	ellipse.Draw(canvas);
	polygon.Draw(canvas);

	cout << canvas.GetResult();

	return 0;
}

