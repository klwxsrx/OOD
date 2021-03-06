#include "stdafx.h"
#include "../libEditor/SvgCanvas.h"
#include "../libEditor/Triangle.h"
#include "../libEditor/Ellipse.h"
#include "../libEditor/Rectangle.h"
#include "../libEditor/GroupShape.h"

std::shared_ptr<CGroupShape> CreateHousePicture()
{
	std::shared_ptr<CRectangle> wall = std::make_shared<CRectangle>(PointD({ 0, 100 }), 200, 200);
	wall->GetOutlineStyle().SetColor(0x663300FF);
	wall->GetFillStyle().Enable(true);
	wall->GetFillStyle().SetColor(0xCC9900FF);

	std::shared_ptr<CRectangle> window = std::make_shared<CRectangle>(PointD({ 75, 175 }), 50, 50);
	window->GetFillStyle().Enable(true);
	window->GetFillStyle().SetColor(0xCCCCCCFF);
	window->GetOutlineStyle().SetColor(0x663300FF);

	std::shared_ptr<CTriangle> roof = std::make_shared<CTriangle>(PointD({ 0, 100 }), PointD({ 100, 0 }), PointD({ 200, 100 }));
	roof->GetFillStyle().Enable(true);
	roof->GetFillStyle().SetColor(0xCC6600FF);

	std::shared_ptr<CEllipse> upperWindow = std::make_shared<CEllipse>(PointD({ 100, 60 }), 20, 20);
	upperWindow->GetFillStyle().Enable(true);
	upperWindow->GetFillStyle().SetColor(0xCCCCCCFF);

	std::shared_ptr<CEllipse> lake = std::make_shared<CEllipse>(PointD({ 450, 250 }), 200, 50);
	lake->GetOutlineStyle().Enable(false);
	lake->GetFillStyle().Enable(true);
	lake->GetFillStyle().SetColor(0x1EBBD7FF);

	std::shared_ptr<CGroupShape> house = std::make_shared<CGroupShape>();
	house->InsertShape(wall);
	house->InsertShape(window);
	house->InsertShape(roof);
	house->InsertShape(upperWindow);
	house->InsertShape(lake);

	RectD pictureFrame = house->GetFrame();
	std::shared_ptr<CRectangle> pictureRect = std::make_shared<CRectangle>(pictureFrame.leftTop, pictureFrame.width, pictureFrame.height);
	pictureRect->GetOutlineStyle().SetStrokeWidth(1.0);
	pictureRect->GetOutlineStyle().SetColor(0x00000011);
	house->InsertShape(pictureRect);
	
	return house;
}

int main()
{	
	std::shared_ptr<CGroupShape> house = CreateHousePicture();
	const auto houseFrame = house->GetFrame();

	CSvgCanvas canvas;
	house->Draw(canvas);

	house->SetFrame({ { houseFrame.leftTop.x, houseFrame.height }, houseFrame.width, 100 });
	house->Draw(canvas);
	
	house->SetFrame({ { houseFrame.width, houseFrame.leftTop.y }, 100, houseFrame.height });
	house->Draw(canvas);

	house->SetFrame({ { houseFrame.leftTop.x, houseFrame.height + 100 }, houseFrame.width, houseFrame.height });
	house->GetFillStyle().Enable(false);
	house->GetOutlineStyle().SetStrokeWidth(4);
	house->GetOutlineStyle().SetColor(0x000000FF);
	house->GetOutlineStyle().Enable(true);
	house->Draw(canvas);

	std::cout << canvas.GetResult() << std::endl;
    return 0;
}

