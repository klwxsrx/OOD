#include "stdafx.h"
#include "SoldOutState.h"


CSoldOutState::CSoldOutState(std::ostream& out)
	: m_out(out)
{
}

void CSoldOutState::InsertQuarter()
{
	m_out << "You can't insert a quarter, the machine is sold out\n";
}

void CSoldOutState::EjectQuarter()
{
	m_out << "You can't eject, you haven't inserted a quarter yet\n";
}

void CSoldOutState::TurnCrank()
{
	m_out << "You turned but there's no gumballs\n";
}

void CSoldOutState::Dispense()
{
	m_out << "No gumball dispensed\n";
}

std::string CSoldOutState::ToString() const
{
	return "sold out";
}