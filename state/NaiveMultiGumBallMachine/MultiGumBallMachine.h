#pragma once

class CGumballMachine final
{
public:
	CGumballMachine(unsigned numBalls, std::ostream& out);

	void InsertQuarter();
	void EjectQuarter();
	void TurnCrank();
	void Refill(unsigned numBalls);
	std::string ToString() const;

private:
	void Dispense();

	void AddQuarter();
	void ReleaseQuarters();
	void HoldQuarter();
	void ReleaseBall();

private:
	enum class State
	{
		NoQuarter,
		HasQuarter,
		Sold,
		SoldOut
	};

	static unsigned MAX_QUARTERS_COUNT;

	State m_state;
	unsigned m_ballsCount;
	unsigned m_quartersCount = 0;
	std::ostream& m_out;
};

