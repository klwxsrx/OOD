#include "stdafx.h"
#include "ShapeFactory.h"

CShapeFactory::CShapeFactory()
	: m_createShapeActionMap({
		{ "Rectangle", std::bind(&CShapeFactory::CreateRectangle, this, std::placeholders::_1) },
		{ "Triangle", std::bind(&CShapeFactory::CreateTriangle, this, std::placeholders::_1) },
		{ "Ellipse", std::bind(&CShapeFactory::CreateEllipse, this, std::placeholders::_1) },
		{ "RegularPolygon", std::bind(&CShapeFactory::CreateRegularPolygon, this, std::placeholders::_1) }
	})
{
}

std::unique_ptr<IShape> CShapeFactory::CreateRectangle(std::istream & input)
{
	CPoint leftTop, rightBottom;
	CColor color;

	input >> leftTop >> rightBottom >> color;

	return std::move(std::make_unique<CRectangle>(leftTop, rightBottom, color.color));
}

std::unique_ptr<IShape> CShapeFactory::CreateTriangle(std::istream & input)
{
	CPoint vertex1, vertex2, vertex3;
	CColor color;

	input >> vertex1 >> vertex2 >> vertex3 >> color;

	return std::move(std::make_unique<CTriangle>(vertex1, vertex2, vertex3, color.color));
}

std::unique_ptr<IShape> CShapeFactory::CreateEllipse(std::istream & input)
{
	CPoint center;
	unsigned horizontalRadius, verticalRadius;
	CColor color;

	input >> center >> horizontalRadius >> verticalRadius >> color;

	return std::move(std::make_unique<CEllipse>(center, horizontalRadius, verticalRadius, color.color));
}

std::unique_ptr<IShape> CShapeFactory::CreateRegularPolygon(std::istream & input)
{
	CPoint center;
	unsigned radius, vertexCount;
	CColor color;

	input >> center >> radius >> vertexCount >> color;

	return std::move(std::make_unique<CRegularPolygon>(center, radius, vertexCount, color.color));
}

std::unique_ptr<IShape> CShapeFactory::CreateShape(const std::string & description)
{
	if (description.empty())
	{
		throw std::runtime_error("Empty shape description entered!");
	}

	std::stringstream stream(description);
	std::string shapeName;

	stream >> shapeName;

	auto it = m_createShapeActionMap.find(shapeName);
	if (it == m_createShapeActionMap.end())
	{
		throw std::runtime_error("Invalid shape type!");
	}

	try
	{
		return it->second(stream);
	}
	catch (std::exception const& e)
	{
		std::string text("Can`t create shape: \"");
		throw std::runtime_error(text.append(description).append("\". Reason: ").append(e.what()));
	}
}