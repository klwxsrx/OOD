#include "stdafx.h"
#include "GumballMachine.h"

unsigned CGumballMachine::MAX_QUARTERS_COUNT = 5;

CGumballMachine::CGumballMachine(unsigned numBalls, std::ostream& out)
	: m_soldState(*this, out)
	, m_soldOutState(*this, out)
	, m_noQuarterState(*this, out)
	, m_hasQuarterState(*this, out)
	, m_state(&m_soldOutState)
	, m_ballsCount(numBalls)
	, m_out(out)
{
	if (m_ballsCount > 0)
	{
		m_state = &m_noQuarterState;
	}
}

void CGumballMachine::InsertQuarter()
{
	m_state->InsertQuarter();
}

void CGumballMachine::EjectQuarter()
{
	m_state->EjectQuarter();
}

void CGumballMachine::TurnCrank()
{
	m_state->TurnCrank();
	m_state->Dispense();
}

std::string CGumballMachine::ToString() const
{
	auto fmt = boost::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: %1% gumball%2%
Money: %3% quarter%4%
Machine is %5%
)");
	return (fmt % m_ballsCount % (m_ballsCount != 1 ? "s" : "") % m_quartersCount % (m_quartersCount != 1 ? "s" : "") % m_state->ToString()).str();
}

void CGumballMachine::ReleaseBall()
{
	if (m_ballsCount != 0)
	{
		m_out << "A gumball comes rolling out the slot...\n";
		--m_ballsCount;
	}
}

unsigned CGumballMachine::GetBallCount() const
{
	return m_ballsCount;
}

void CGumballMachine::AddQuarter()
{
	++m_quartersCount;
	m_out << "A quarter fell into money receiver...\n";
}

void CGumballMachine::ReleaseQuarters()
{
	if (m_quartersCount != 0)
	{
		m_out << "A " << m_quartersCount << " quarter comes rolling out the money slot...\n";
		m_quartersCount = 0;
	}
}

void CGumballMachine::HoldQuarter()
{
	if (m_quartersCount != 0)
	{
		--m_quartersCount;
	}
}

unsigned CGumballMachine::GetQuartersCount() const
{
	return m_quartersCount;
}

unsigned CGumballMachine::GetMaxQuartersCount() const
{
	return MAX_QUARTERS_COUNT;
}

void CGumballMachine::SetSoldOutState()
{
	m_state = &m_soldOutState;
}

void CGumballMachine::SetNoQuarterState()
{
	m_state = &m_noQuarterState;
}

void CGumballMachine::SetSoldState()
{
	m_state = &m_soldState;
}

void CGumballMachine::SetHasQuarterState()
{
	m_state = &m_hasQuarterState;
}
