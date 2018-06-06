#include "stdafx.h"
#include "HasQuarterState.h"

CHasQuarterState::CHasQuarterState(IGumballMachine& gumballMachine, std::ostream& out)
	: m_gumballMachine(gumballMachine), m_out(out)
{
}

void CHasQuarterState::InsertQuarter()
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

void CHasQuarterState::EjectQuarter()
{
	m_out << "Quarter(s) returned\n";
	m_gumballMachine.ReleaseQuarters();
	m_gumballMachine.SetNoQuarterState();
}

void CHasQuarterState::TurnCrank()
{
	m_out << "You turned...\n";
	m_gumballMachine.SetSoldState();
}

void CHasQuarterState::Dispense()
{
	m_out << "No gumball dispensed\n";
}

void CHasQuarterState::Refill(unsigned numBalls)
{
	m_gumballMachine.SetBallsCount(numBalls);
	if (m_gumballMachine.GetBallCount() == 0)
	{
		m_gumballMachine.SetSoldOutState();
	}
}

std::string CHasQuarterState::ToString() const
{
	return "waiting for turn of crank";
}