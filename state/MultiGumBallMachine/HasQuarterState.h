#pragma once
#include "IState.h"
#include "IGumballMachine.h"

class CHasQuarterState final : public IState
{
public:
	CHasQuarterState(IGumballMachine& gumballMachine, std::ostream& out);

	void InsertQuarter() override;
	void EjectQuarter() override;
	void TurnCrank() override;
	void Dispense() override;
	std::string ToString() const override;

private:
	IGumballMachine& m_gumballMachine;
	std::ostream& m_out;
};