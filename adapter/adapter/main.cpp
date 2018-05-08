#include "stdafx.h"
#include "graphics_lib.h"
#include "shape_drawing_lib.h"
#include "modern_graphics_lib.h"
#include "CanvasAdapter.h"
#include "CanvasAdapterViaInheritance.h"

// Пространство имен приложения (доступно для модификации)
namespace app
{
	void PaintPicture(shape_drawing_lib::CCanvasPainter & painter)
	{
		using namespace shape_drawing_lib;

		CTriangle triangle({ 10, 15 }, { 100, 200 }, { 150, 250 }, 0x00FF00AA);
		CRectangle rectangle({ 30, 40 }, 18, 24, 0xFF00FFFF);

		painter.Draw(triangle);
		painter.Draw(rectangle);
	}

	void PaintPictureOnCanvas()
	{
		graphics_lib::CCanvas simpleCanvas;
		shape_drawing_lib::CCanvasPainter painter(simpleCanvas);
		PaintPicture(painter);
	}

	void PaintPictureOnModernGraphicsRenderer()
	{
		#if true
			modern_graphics_lib::CModernGraphicsRenderer renderer(std::cout);
			CCanvasAdapter adapter(renderer);
		#else
			CCanvasAdapterViaInheritance adapter(std::cout);
		#endif

		shape_drawing_lib::CCanvasPainter painter(adapter);
		PaintPicture(painter);
	}
}

int main()
{
	std::cout << "Should we use new API (y)?";
	std::string userInput;
	if (getline(std::cin, userInput) && (userInput == "y" || userInput == "Y"))
	{
		app::PaintPictureOnModernGraphicsRenderer();
	}
	else
	{
		app::PaintPictureOnCanvas();
	}

	return 0;
}