#pragma once
#include "../MultiGumBallMachine/GumballMachine.h"

class CMachineControlPanel
{
public:
	CMachineControlPanel(CGumballMachine& gumballMachine, std::istream& in, std::ostream& out);

	void HandleCommand();
	void PrintHelp();
	void PrintMachineState();

private:
	void InsertQuarter(std::istream& args);
	void EjectQuarter(std::istream& args);
	void TurnCrank(std::istream& args);
	void Refill(std::istream& args);

	void PrintCarriage();
	void ClearConsole();

	typedef std::map<std::string, std::function<void(std::istream& args)>> ActionMap;
	
	const ActionMap m_actionMap;
	std::istream& m_input;
	std::ostream& m_output;
	CGumballMachine& m_machine;
};

