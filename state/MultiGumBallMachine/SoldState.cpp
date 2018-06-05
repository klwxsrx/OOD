#include "stdafx.h"
#include "SoldState.h"

CSoldState::CSoldState(IGumballMachine& gumballMachine, std::ostream& out)
	: m_gumballMachine(gumballMachine), m_out(out)
{
}

void CSoldState::InsertQuarter()
{
	if (m_gumballMachine.GetQuartersCount() != m_gumballMachine.GetMaxQuartersCount())
	{
		m_out << "You inserted a quarter\n";
		m_gumballMachine.AddQuarter();
	}
	else
	{
		m_out << "You can't insert another one quarter\n";
	}
}

void CSoldState::EjectQuarter()
{
	m_out << "Sorry you already turned the crank\n";
}

void CSoldState::TurnCrank()
{
	m_out << "Please wait, we're already giving you a gumball\n";
}

void CSoldState::Dispense()
{
	m_gumballMachine.HoldQuarter();
	m_gumballMachine.ReleaseBall();
	if (m_gumballMachine.GetBallCount() == 0)
	{
		m_out << "Oops, out of gumballs\n";
		m_gumballMachine.SetSoldOutState();
	}
	else if (m_gumballMachine.GetQuartersCount() == 0)
	{
		m_gumballMachine.SetNoQuarterState();
	}
	else
	{
		m_gumballMachine.SetHasQuarterState();
	}
}

std::string CSoldState::ToString() const
{
	return "delivering a gumball";
}