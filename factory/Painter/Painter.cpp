#include "stdafx.h"
#include "../libpainter/ShapeFactory.h"
#include "../libpainter/Designer.h"
#include "../libpainter/PictureDraft.h"
#include "../libpainter/SvgCanvas.h"
#include "../libpainter/Painter.h"

int main()
{
	CShapeFactory factory;
	CDesigner designer(factory);

	try
	{
		CPictureDraft draft = designer.CreateDraft(std::cin);
		CSvgCanvas canvas;

		CPainter painter;
		painter.DrawPicture(draft, canvas);

		std::cout << canvas.GetResult() << std::endl;
	}
	catch (std::runtime_error const& e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}

