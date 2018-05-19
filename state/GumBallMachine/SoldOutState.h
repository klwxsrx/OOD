#pragma once
#include "IState.h"

class CSoldOutState final : public IState
{
public:
	CSoldOutState(std::ostream& out);

	void InsertQuarter() override;
	void EjectQuarter() override;
	void TurnCrank() override;
	void Dispense() override;
	std::string ToString() const override;

private:
	std::ostream& m_out;
};