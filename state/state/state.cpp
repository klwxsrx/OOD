#include "stdafx.h"
#include "../MultiGumBallMachine/GumballMachine.h"
#include "MachineControlPanel.h"

int main()
{
	CGumballMachine machine(5, std::cout);
	CMachineControlPanel controlPanel(machine, std::cin, std::cout);

	while (!std::cin.eof() && !std::cin.fail())
	{
		controlPanel.HandleCommand();
	}
}

