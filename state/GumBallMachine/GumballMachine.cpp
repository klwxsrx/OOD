#include "stdafx.h"
#include "GumballMachine.h"

CGumballMachine::CGumballMachine(unsigned numBalls, std::ostream& out)
	: m_soldState(*this, out)
	, m_soldOutState(out)
	, m_noQuarterState(*this, out)
	, m_hasQuarterState(*this, out)
	, m_state(&m_soldOutState)
	, m_count(numBalls)
	, m_out(out)
{
	if (m_count > 0)
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
Machine is %3%
)");
	return (fmt % m_count % (m_count != 1 ? "s" : "") % m_state->ToString()).str();
}

void CGumballMachine::ReleaseBall()
{
	if (m_count != 0)
	{
		m_out << "A gumball comes rolling out the slot...\n";
		--m_count;
	}
}

unsigned CGumballMachine::GetBallCount() const
{
	return m_count;
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
