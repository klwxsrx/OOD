#pragma once
#include "IShapeFactory.h"
#include "Shape.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Ellipse.h"
#include "RegularPolygon.h"

class CShapeFactory : public IShapeFactory
{
public:
	CShapeFactory();
	~CShapeFactory() = default;

	std::unique_ptr<CShape> CreateShape(const std::string & description)override;

private:
	//static Color ReadColor(std::istream & input);

	std::unique_ptr<CShape> CreateRectangle(std::istream & input);
	std::unique_ptr<CShape> CreateTriangle(std::istream & input);
	std::unique_ptr<CShape> CreateEllipse(std::istream & input);
	std::unique_ptr<CShape> CreateRegularPolygon(std::istream & input);

	const std::map<std::string, std::function<std::unique_ptr<CShape> (std::istream&)>> m_createShapeActionMap;
};