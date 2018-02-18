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

// Размер порции кофе
enum class CoffeeSize { Standard, Double };

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
	CCapuccino(CoffeeSize size = CoffeeSize::Standard)
		: CCoffee((size == CoffeeSize::Standard) ? "Capuccino" : "Double capuccino")
		, m_size(size)
	{}

	double GetCost() const override 
	{
		return (m_size == CoffeeSize::Standard) ? 80 : 120;
	}
private:
	CoffeeSize m_size;
};

// Латте
class CLatte : public CCoffee
{
public:
	CLatte(CoffeeSize size = CoffeeSize::Standard)
		: CCoffee((size == CoffeeSize::Standard) ? "Latte" : "Double latte")
		, m_size(size)
	{}

	double GetCost() const override 
	{
		return (m_size == CoffeeSize::Standard) ? 90 : 130;
	}
private:
	CoffeeSize m_size;
};

// Сорт чая
enum TeaGrade { BlackTea, GreenTea, HerbalTea, OolongTea };

// Чай
class CTea : public CBeverage
{
public:
	CTea(TeaGrade grade = BlackTea)
		: CBeverage(GetDescriptionByGrade(grade))
	{}

	double GetCost() const override 
	{
		return 30; 
	}
private:
	static std::string GetDescriptionByGrade(TeaGrade grade)
	{
		std::string gradeName;
		switch (grade)
		{
		case TeaGrade::GreenTea:
			gradeName = "Green";
			break;
		case TeaGrade::HerbalTea:
			gradeName = "Herbal";
			break;
		case TeaGrade::OolongTea:
			gradeName = "Oolong";
			break;
		case TeaGrade::BlackTea:
		default:
			gradeName = "Black";
		}
		return gradeName.append(" tea");
	}
};

// Размер порции молочного коктейля
enum class MilkshakeSize { Small, Standard, Big };

// Молочный коктейль
class CMilkshake : public CBeverage
{
public:
	CMilkshake(MilkshakeSize size = MilkshakeSize::Standard)
		: CBeverage(GetDescriptionBySize(size))
		, m_size(size)
	{}

	double GetCost() const override 
	{ 
		return GetCostBySize(m_size);
	}
private:
	MilkshakeSize m_size;

	static std::string GetDescriptionBySize(MilkshakeSize size)
	{
		switch (size)
		{
		case MilkshakeSize::Small:
			return "Small milkshake";
		case MilkshakeSize::Big:
			return "Big milkshake";
		case MilkshakeSize::Standard:
		default:
			return "Milkshake";
		}
	}

	static double GetCostBySize(MilkshakeSize size)
	{
		switch (size)
		{
		case MilkshakeSize::Small:
			return 50;
		case MilkshakeSize::Big:
			return 80;
		case MilkshakeSize::Standard:
		default:
			return 60;
		}
	}
};
