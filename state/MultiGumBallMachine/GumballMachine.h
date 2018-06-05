#pragma once
#include "IGumballMachine.h"
#include "SoldState.h"
#include "SoldOutState.h"
#include "NoQuarterState.h"
#include "HasQuarterState.h"

class CGumballMachine final : private IGumballMachine
{
public:
	CGumballMachine(unsigned numBalls, std::ostream& out);

	void InsertQuarter();
	void EjectQuarter();
	void TurnCrank();
	std::string ToString() const;

private:
	void ReleaseBall() override;
	unsigned GetBallCount() const override;
	void AddQuarter() override;
	void ReleaseQuarters() override;
	void HoldQuarter() override;

	unsigned GetQuartersCount() const override;
	unsigned GetMaxQuartersCount() const override;
	void SetSoldOutState() override;
	void SetNoQuarterState() override;
	void SetSoldState() override;
	void SetHasQuarterState() override;

private:
	static unsigned MAX_QUARTERS_COUNT;

	unsigned m_ballsCount;
	unsigned m_quartersCount = 0;
	CSoldState m_soldState;
	CSoldOutState m_soldOutState;
	CNoQuarterState m_noQuarterState;
	CHasQuarterState m_hasQuarterState;
	IState* m_state;
	std::ostream& m_out;
};

