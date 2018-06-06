#include "stdafx.h"
#include "MachineControlPanel.h"

CMachineControlPanel::CMachineControlPanel(CGumballMachine& gumballMachine, std::istream& in, std::ostream& out)
	: m_machine(gumballMachine), m_input(in), m_output(out)
	, m_actionMap({
		{ "InsertQuarter", std::bind(&CMachineControlPanel::InsertQuarter, this, std::placeholders::_1) },
		{ "EjectQuarter", std::bind(&CMachineControlPanel::EjectQuarter, this, std::placeholders::_1) },
		{ "TurnCrank", std::bind(&CMachineControlPanel::TurnCrank, this, std::placeholders::_1) },
		{ "Refill", std::bind(&CMachineControlPanel::Refill, this, std::placeholders::_1) },
	})
{
	PrintHelp();
	PrintMachineState();
	PrintCarriage();
}

void CMachineControlPanel::HandleCommand()
{
	std::string commandLine;
	std::getline(m_input, commandLine);
	std::istringstream strm(commandLine);

	std::string action;
	strm >> action;

	ClearConsole();

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		try
		{
			it->second(strm);
		}
		catch (const std::exception& e)
		{
			m_output << e.what() << std::endl;
		}
	}
	else
	{
		m_output << "Unknown command!" << std::endl << std::endl;
		PrintHelp();
	}

	PrintMachineState();
	PrintCarriage();
}

void CMachineControlPanel::PrintHelp()
{
	m_output << "InsertQuarter" << std::endl
		<< "EjectQuarter" << std::endl
		<< "TurnCrank" << std::endl
		<< "Refill <number>" << std::endl;
}

void CMachineControlPanel::PrintMachineState()
{
	m_output << m_machine.ToString() << std::endl;
}

void CMachineControlPanel::InsertQuarter(std::istream& args)
{
	m_machine.InsertQuarter();
}

void CMachineControlPanel::EjectQuarter(std::istream& args)
{
	m_machine.EjectQuarter();
}

void CMachineControlPanel::TurnCrank(std::istream& args)
{
	m_machine.TurnCrank();
}

void CMachineControlPanel::Refill(std::istream& args)
{
	unsigned ballsCount;
	args >> ballsCount;
	if (args.fail())
	{
		throw std::runtime_error("Unsigned number required!");
	}

	m_machine.Refill(ballsCount);
}

void CMachineControlPanel::PrintCarriage()
{
	m_output << std::endl << "> ";
}

void CMachineControlPanel::ClearConsole()
{
	system("cls");
}