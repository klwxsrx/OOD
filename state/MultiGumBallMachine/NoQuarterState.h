#pragma once
#include "IState.h"
#include "IGumballMachine.h"

class CNoQuarterState final : public IState
{
public:
	CNoQuarterState(IGumballMachine& gumballMachine, std::ostream& out);

	void InsertQuarter() override;
	void EjectQuarter() override;
	void TurnCrank() override;
	void Dispense() override;
	void Refill(unsigned numBalls) override;
	std::string ToString() const override;

private:
	IGumballMachine& m_gumballMachine;
	std::ostream& m_out;
};