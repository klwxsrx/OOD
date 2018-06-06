#include "stdafx.h"
#include "SoldOutState.h"


CSoldOutState::CSoldOutState(IGumballMachine& gumballMachine, std::ostream& out)
	: m_gumballMachine(gumballMachine), m_out(out)
{
}

void CSoldOutState::InsertQuarter()
{
	m_out << "You can't insert a quarter, the machine is sold out\n";
}

void CSoldOutState::EjectQuarter()
{
	if (m_gumballMachine.GetQuartersCount() == 0)
	{
		m_out << "You can't eject, you haven't inserted a quarter(s)\n";
	}
	else
	{
		m_out << "Quarter(s) returned\n";
		m_gumballMachine.ReleaseQuarters();
	}
}

void CSoldOutState::TurnCrank()
{
	m_out << "You turned but there's no gumballs\n";
}

void CSoldOutState::Dispense()
{
	m_out << "No gumball dispensed\n";
}

void CSoldOutState::Refill(unsigned numBalls)
{
	m_gumballMachine.SetBallsCount(numBalls);
	if (m_gumballMachine.GetBallCount() == 0)
	{
		return;
	}

	if (m_gumballMachine.GetQuartersCount() == 0)
	{
		m_gumballMachine.SetNoQuarterState();
	}
	else
	{
		m_gumballMachine.SetHasQuarterState();
	}
}

std::string CSoldOutState::ToString() const
{
	return "sold out";
}