#pragma once

#include <string>
#include <memory>


// Интерфейс "напиток"
class IBeverage
{
public:
	virtual std::string GetDescriptionByGrade() const = 0;
	virtual double GetCost()const = 0;
	virtual ~IBeverage() = default;
};

typedef std::unique_ptr<IBeverage> IBeveragePtr;
