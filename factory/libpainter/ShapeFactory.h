#pragma once
#include "IShapeFactory.h"
#include "IShape.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Ellipse.h"
#include "RegularPolygon.h"

class CShapeFactory : public IShapeFactory
{
public:
	CShapeFactory();
	~CShapeFactory() = default;

	std::unique_ptr<IShape> CreateShape(const std::string & description)override;

private:
	std::unique_ptr<IShape> CreateRectangle(std::istream & input);
	std::unique_ptr<IShape> CreateTriangle(std::istream & input);
	std::unique_ptr<IShape> CreateEllipse(std::istream & input);
	std::unique_ptr<IShape> CreateRegularPolygon(std::istream & input);

	const std::map<std::string, std::function<std::unique_ptr<IShape> (std::istream&)>> m_createShapeActionMap;
};