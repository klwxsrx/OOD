#include "stdafx.h"
#include "NoQuarterState.h"

CNoQuarterState::CNoQuarterState(IGumballMachine& gumballMachine, std::ostream& out)
	: m_gumballMachine(gumballMachine), m_out(out)
{
}

void CNoQuarterState::InsertQuarter()
{
	m_out << "You inserted a quarter\n";
	m_gumballMachine.AddQuarter();
	m_gumballMachine.SetHasQuarterState();
}

void CNoQuarterState::EjectQuarter()
{
	m_out << "You haven't inserted a quarter\n";
}

void CNoQuarterState::TurnCrank()
{
	m_out << "You turned but there's no quarter\n";
}

void CNoQuarterState::Dispense()
{
	m_out << "You need to pay first\n";
}

void CNoQuarterState::Refill(unsigned numBalls)
{
	m_gumballMachine.SetBallsCount(numBalls);
	if (m_gumballMachine.GetBallCount() == 0)
	{
		m_gumballMachine.SetSoldOutState();
	}
}

std::string CNoQuarterState::ToString() const
{
	return "waiting for quarter";
}