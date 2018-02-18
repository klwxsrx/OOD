#pragma once
#include "IBeverage.h"

// Базовая реализация напитка, предоставляющая его описание
class CBeverage : public IBeverage
{
public:
	CBeverage(const std::string & description)
		:m_description(description)
	{}

	std::string GetDescriptionByGrade()const override final
	{
		return m_description;
	}
private:
	std::string m_description;
};

// Кофе
class CCoffee : public CBeverage
{
public:
	CCoffee(const std::string& description = "Coffee")
		:CBeverage(description) 
	{}

	double GetCost() const override 
	{
		return 60; 
	}
};

// Капуччино
class CCapuccino : public CCoffee
{
public:
	enum Size { Standard, Double };

	CCapuccino(Size size = Size::Standard)
		: CCoffee((size == Size::Standard) ? "Capuccino" : "Double capuccino")
		, m_size(size)
	{}

	double GetCost() const override 
	{
		return (m_size == Size::Standard) ? 80 : 120;
	}
private:
	Size m_size;
};

// Латте
class CLatte : public CCoffee
{
public:
	enum Size { Standard, Double };

	CLatte(Size size = Size::Standard) 
		: CCoffee((size == Size::Standard) ? "Latte" : "Double latte")
		, m_size(size)
	{}

	double GetCost() const override 
	{
		return (m_size == Size::Standard) ? 90 : 130;
	}
private:
	Size m_size;
};

// Чай
class CTea : public CBeverage
{
public:
	enum Grade { BlackTea, GreenTea, HerbalTea, OolongTea };

	CTea(Grade grade = BlackTea)
		: CBeverage(GetDescriptionByGrade(grade))
	{}

	double GetCost() const override 
	{
		return 30; 
	}
private:
	static std::string GetDescriptionByGrade(Grade grade)
	{
		std::string gradeName;
		switch (grade)
		{
		case Grade::GreenTea:
			gradeName = "Green";
			break;
		case Grade::HerbalTea:
			gradeName = "Herbal";
			break;
		case Grade::OolongTea:
			gradeName = "Oolong";
			break;
		case Grade::BlackTea:
		default:
			gradeName = "Black";
		}
		return gradeName.append(" tea");
	}
};

// Молочный коктейль
class CMilkshake : public CBeverage
{
public:
	enum Size { Small, Standard, Big };

	CMilkshake(Size size = CMilkshake::Standard) 
		: CBeverage(GetDescriptionBySize(size))
		, m_size(size)
	{}

	double GetCost() const override 
	{ 
		return GetCostBySize(m_size);
	}
private:
	Size m_size;

	static std::string GetDescriptionBySize(Size size)
	{
		switch (size)
		{
		case CMilkshake::Small:
			return "Small milkshake";
		case CMilkshake::Big:
			return "Big milkshake";
		case CMilkshake::Standard:
		default:
			return "Milkshake";
		}
	}

	static double GetCostBySize(Size size)
	{
		switch (size)
		{
		case CMilkshake::Small:
			return 50;
		case CMilkshake::Big:
			return 80;
		case CMilkshake::Standard:
		default:
			return 60;
		}
	}
};
