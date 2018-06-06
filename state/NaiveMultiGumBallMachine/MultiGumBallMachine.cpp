#include "stdafx.h"
#include "MultiGumBallMachine.h"

unsigned CGumballMachine::MAX_QUARTERS_COUNT = 5;

CGumballMachine::CGumballMachine(unsigned numBalls, std::ostream& out)
	: m_ballsCount(numBalls)
	, m_out(out)
{
	m_state = (m_ballsCount == 0) ? State::SoldOut : State::NoQuarter;
}

void CGumballMachine::InsertQuarter()
{
	switch (m_state)
	{
	case State::NoQuarter:
		m_out << "You inserted a quarter\n";
		AddQuarter();
		m_state = State::HasQuarter;
		break;

	case State::HasQuarter:
	case State::Sold:
		if (m_quartersCount != MAX_QUARTERS_COUNT)
		{
			m_out << "You inserted a quarter\n";
			AddQuarter();
		}
		else
		{
			m_out << "You can't insert another one quarter\n";
		}
		break;

	case State::SoldOut:
		m_out << "You can't insert a quarter, the machine is sold out\n";
		break;
	}
}

void CGumballMachine::EjectQuarter()
{
	switch (m_state)
	{
	case State::NoQuarter:
		m_out << "You haven't inserted a quarter\n";
		break;

	case State::HasQuarter:
		m_out << "Quarter(s) returned\n";
		ReleaseQuarters();
		m_state = State::NoQuarter;
		break;

	case State::Sold:
		m_out << "Sorry you already turned the crank\n";
		break;

	case State::SoldOut:
		if (m_quartersCount == 0)
		{
			m_out << "You can't eject, you haven't inserted a quarter(s)\n";
		}
		else
		{
			m_out << "Quarter(s) returned\n";
			ReleaseQuarters();
		}
		break;
	}
}

void CGumballMachine::TurnCrank()
{
	switch (m_state)
	{
	case State::NoQuarter:
		m_out << "You turned but there's no quarter\n";
		break;

	case State::HasQuarter:
		m_out << "You turned...\n";
		m_state = State::Sold;
		break;

	case State::Sold:
		m_out << "Please wait, we're already giving you a gumball\n";
		break;

	case State::SoldOut:
		m_out << "You turned but there's no gumballs\n";
		break;
	}
	Dispense();
}

void CGumballMachine::Refill(unsigned numBalls)
{
	switch (m_state)
	{
	case State::NoQuarter:
	case State::HasQuarter:
	case State::SoldOut:
		m_ballsCount = numBalls;
		if (m_ballsCount == 0)
		{
			m_state = State::SoldOut;
			m_out << "The machine has emptied\n";
		}
		else
		{
			m_state = (m_quartersCount == 0) ? State::NoQuarter : State::HasQuarter;
			m_out << "The machine has refilled\n";
		}
		break;

	case State::Sold:
		m_out << "You can't refill machine while machine dispense gumball\n";
		break;
	}
}

std::string CGumballMachine::ToString() const
{
	std::string state =
		(m_state == State::SoldOut) ? "sold out" :
		(m_state == State::NoQuarter) ? "waiting for quarter" :
		(m_state == State::HasQuarter) ? "waiting for turn of crank"
		: "delivering a gumball";

	auto fmt = boost::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: %1% gumball%2%
Money: %3% quarter%4%
Machine is %5%
)");
	return (fmt % m_ballsCount % (m_ballsCount != 1 ? "s" : "") % m_quartersCount % (m_quartersCount != 1 ? "s" : "") % state).str();
}

void CGumballMachine::Dispense()
{
	switch (m_state)
	{
	case State::NoQuarter:
		m_out << "You need to pay first\n";
		break;

	case State::HasQuarter:
		m_out << "No gumball dispensed\n";
		break;

	case State::Sold:
		HoldQuarter();
		ReleaseBall();
		if (m_ballsCount == 0)
		{
			m_out << "Oops, out of gumballs\n";
			m_state = State::SoldOut;
		}
		else if (m_quartersCount == 0)
		{
			m_state = State::NoQuarter;
		}
		else
		{
			m_state = State::HasQuarter;
		}
		break;

	case State::SoldOut:
		m_out << "No gumball dispensed\n";
		break;
	}
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

void CGumballMachine::ReleaseBall()
{
	if (m_ballsCount != 0)
	{
		m_out << "A gumball comes rolling out the slot...\n";
		--m_ballsCount;
	}
}