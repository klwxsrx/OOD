#pragma once

class IGumballMachine
{
public:
	virtual void SetBallsCount(unsigned) = 0;
	virtual void ReleaseBall() = 0;
	virtual unsigned GetBallCount() const = 0;
	virtual void AddQuarter() = 0;
	virtual void ReleaseQuarters() = 0;
	virtual void HoldQuarter() = 0;
	virtual unsigned GetQuartersCount() const = 0;
	virtual unsigned GetMaxQuartersCount() const = 0;

	virtual void SetSoldOutState() = 0;
	virtual void SetNoQuarterState() = 0;
	virtual void SetSoldState() = 0;
	virtual void SetHasQuarterState() = 0;

	virtual ~IGumballMachine() = default;
};
