#include "stdafx.h"
#include "../MultiGumBallMachine/GumballMachine.h"

struct GumballMachineFixture
{
	CGumballMachine machine;
	std::ostringstream outputStream;
	GumballMachineFixture()
		: machine(3, outputStream)
	{
	}

	void ClearOutputStream()
	{
		outputStream.str("");
		outputStream.clear();
	}
};

BOOST_FIXTURE_TEST_SUITE(GumballMachine, GumballMachineFixture)

	BOOST_AUTO_TEST_SUITE(when_created)

		BOOST_AUTO_TEST_CASE(has_predetermined_state_and_balls_count)
		{
			BOOST_CHECK_EQUAL(machine.ToString(), R"text(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: 3 gumballs
Money: 0 quarters
Machine is waiting for quarter
)text");
		}

		BOOST_AUTO_TEST_SUITE(when_in_no_quarter_state)

			BOOST_AUTO_TEST_CASE(is_waiting_for_turn_crank_after_quarter_insert)
			{
				machine.InsertQuarter();
				BOOST_CHECK_EQUAL(outputStream.str(), "You inserted a quarter\nA quarter fell into money receiver...\n");
				BOOST_CHECK_EQUAL(machine.ToString(), R"text(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: 3 gumballs
Money: 1 quarter
Machine is waiting for turn of crank
)text");
			}

			BOOST_AUTO_TEST_CASE(cant_eject_quarter)
			{
				machine.EjectQuarter();
				auto result = outputStream.str();
				BOOST_CHECK_EQUAL(outputStream.str(), "You haven't inserted a quarter\n");
				BOOST_CHECK_EQUAL(machine.ToString(), R"text(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: 3 gumballs
Money: 0 quarters
Machine is waiting for quarter
)text");
			}

			BOOST_AUTO_TEST_CASE(nothing_happens_when_turns_the_crank)
			{
				machine.TurnCrank();
				BOOST_CHECK_EQUAL(outputStream.str(), "You turned but there's no quarter\nYou need to pay first\n");
				BOOST_CHECK_EQUAL(machine.ToString(), R"text(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: 3 gumballs
Money: 0 quarters
Machine is waiting for quarter
)text");
			}

		BOOST_AUTO_TEST_SUITE_END()

		struct GumballMachineWithInsertedQuarterFixture : public GumballMachineFixture
		{
			GumballMachineWithInsertedQuarterFixture()
			{
				machine.InsertQuarter();
				ClearOutputStream();
			}
		};

		BOOST_FIXTURE_TEST_SUITE(when_in_has_quarter_state, GumballMachineWithInsertedQuarterFixture)

			BOOST_AUTO_TEST_CASE(can_insert_five_quarters)
			{
				machine.InsertQuarter();
				BOOST_CHECK_EQUAL(outputStream.str(), "You inserted a quarter\nA quarter fell into money receiver...\n");
				BOOST_CHECK_EQUAL(machine.ToString(), R"text(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: 3 gumballs
Money: 2 quarters
Machine is waiting for turn of crank
)text");

				machine.InsertQuarter();
				machine.InsertQuarter();
				machine.InsertQuarter();
				BOOST_CHECK_EQUAL(machine.ToString(), R"text(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: 3 gumballs
Money: 5 quarters
Machine is waiting for turn of crank
)text");

				ClearOutputStream();
				machine.InsertQuarter();
				BOOST_CHECK_EQUAL(outputStream.str(), "You can't insert another one quarter\n");
				BOOST_CHECK_EQUAL(machine.ToString(), R"text(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: 3 gumballs
Money: 5 quarters
Machine is waiting for turn of crank
)text");
			}

			BOOST_AUTO_TEST_CASE(can_eject_last_quarter)
			{
				machine.EjectQuarter();
				BOOST_CHECK_EQUAL(outputStream.str(), "Quarter(s) returned\nA 1 quarter comes rolling out the money slot...\n");
				BOOST_CHECK_EQUAL(machine.ToString(), R"text(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: 3 gumballs
Money: 0 quarters
Machine is waiting for quarter
)text");
			}

			BOOST_AUTO_TEST_CASE(can_eject_some_quarters)
			{
				machine.InsertQuarter();
				machine.InsertQuarter();
				ClearOutputStream();

				machine.EjectQuarter();
				BOOST_CHECK_EQUAL(outputStream.str(), "Quarter(s) returned\nA 3 quarter comes rolling out the money slot...\n");
				BOOST_CHECK_EQUAL(machine.ToString(), R"text(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: 3 gumballs
Money: 0 quarters
Machine is waiting for quarter
)text");
			}

			BOOST_AUTO_TEST_CASE(dispense_gumball_after_turn_crank_with_last_quarter)
			{
				machine.TurnCrank();
				BOOST_CHECK_EQUAL(outputStream.str(), "You turned...\nA gumball comes rolling out the slot...\n");
				BOOST_CHECK_EQUAL(machine.ToString(), R"text(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: 2 gumballs
Money: 0 quarters
Machine is waiting for quarter
)text");
			}

			BOOST_AUTO_TEST_CASE(dispense_gumball_after_turn_crank_with_some_quarters)
			{
				machine.InsertQuarter();
				machine.InsertQuarter();
				ClearOutputStream();

				machine.TurnCrank();
				BOOST_CHECK_EQUAL(outputStream.str(), "You turned...\nA gumball comes rolling out the slot...\n");
				BOOST_CHECK_EQUAL(machine.ToString(), R"text(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: 2 gumballs
Money: 2 quarters
Machine is waiting for turn of crank
)text");
			}

			BOOST_AUTO_TEST_CASE(dispense_last_gumball_after_turn_crank_with_last_quarter)
			{
				machine.TurnCrank();

				machine.InsertQuarter();
				machine.TurnCrank();

				machine.InsertQuarter();
				ClearOutputStream();

				machine.TurnCrank();
				BOOST_CHECK_EQUAL(outputStream.str(), "You turned...\nA gumball comes rolling out the slot...\nOops, out of gumballs\n");
				BOOST_CHECK_EQUAL(machine.ToString(), R"text(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: 0 gumballs
Money: 0 quarters
Machine is sold out
)text");
			}

			BOOST_AUTO_TEST_CASE(dispense_last_gumball_after_turn_crank_with_some_quarters)
			{
				machine.TurnCrank();

				machine.InsertQuarter();
				machine.TurnCrank();

				machine.InsertQuarter();
				machine.InsertQuarter();
				machine.InsertQuarter();
				ClearOutputStream();

				machine.TurnCrank();
				BOOST_CHECK_EQUAL(outputStream.str(), "You turned...\nA gumball comes rolling out the slot...\nOops, out of gumballs\n");
				BOOST_CHECK_EQUAL(machine.ToString(), R"text(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: 0 gumballs
Money: 2 quarters
Machine is sold out
)text");
			}

		BOOST_AUTO_TEST_SUITE_END()

		struct GumballMachineWithSoldOutGumballsWithQuartersFixture : public GumballMachineWithInsertedQuarterFixture
		{
			GumballMachineWithSoldOutGumballsWithQuartersFixture()
			{
				machine.TurnCrank();

				machine.InsertQuarter();
				machine.TurnCrank();

				machine.InsertQuarter();
				machine.InsertQuarter();
				machine.InsertQuarter();
				machine.TurnCrank();

				ClearOutputStream();
			}
		};

		BOOST_FIXTURE_TEST_SUITE(when_in_sold_out_state_with_quarters, GumballMachineWithSoldOutGumballsWithQuartersFixture)

			BOOST_AUTO_TEST_CASE(cant_insert_quarter)
			{
				machine.InsertQuarter();
				BOOST_CHECK_EQUAL(outputStream.str(), "You can't insert a quarter, the machine is sold out\n");
				BOOST_CHECK_EQUAL(machine.ToString(), R"text(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: 0 gumballs
Money: 2 quarters
Machine is sold out
)text");
			}

			BOOST_AUTO_TEST_CASE(can_eject_quarter)
			{
				machine.EjectQuarter();
				BOOST_CHECK_EQUAL(outputStream.str(), "Quarter(s) returned\nA 2 quarter comes rolling out the money slot...\n");
				BOOST_CHECK_EQUAL(machine.ToString(), R"text(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: 0 gumballs
Money: 0 quarters
Machine is sold out
)text");
			}

			BOOST_AUTO_TEST_CASE(nothing_happens_when_turns_the_crank)
			{
				machine.TurnCrank();
				BOOST_CHECK_EQUAL(outputStream.str(), "You turned but there's no gumballs\nNo gumball dispensed\n");
				BOOST_CHECK_EQUAL(machine.ToString(), R"text(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: 0 gumballs
Money: 2 quarters
Machine is sold out
)text");
			}

		BOOST_AUTO_TEST_SUITE_END()

		struct GumballMachineWithSoldOutGumballsWithoutQuartersFixture : public GumballMachineWithSoldOutGumballsWithQuartersFixture
		{
			GumballMachineWithSoldOutGumballsWithoutQuartersFixture()
			{
				machine.EjectQuarter();
				ClearOutputStream();
			}
		};

		BOOST_FIXTURE_TEST_SUITE(when_in_sold_out_state_without_quarters, GumballMachineWithSoldOutGumballsWithoutQuartersFixture)

			BOOST_AUTO_TEST_CASE(cant_insert_quarter)
		{
			machine.InsertQuarter();
			BOOST_CHECK_EQUAL(outputStream.str(), "You can't insert a quarter, the machine is sold out\n");
			BOOST_CHECK_EQUAL(machine.ToString(), R"text(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: 0 gumballs
Money: 0 quarters
Machine is sold out
)text");
		}

		BOOST_AUTO_TEST_CASE(cant_eject_quarter)
		{
			machine.EjectQuarter();
			BOOST_CHECK_EQUAL(outputStream.str(), "You can't eject, you haven't inserted a quarter(s)\n");
			BOOST_CHECK_EQUAL(machine.ToString(), R"text(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: 0 gumballs
Money: 0 quarters
Machine is sold out
)text");
		}

		BOOST_AUTO_TEST_CASE(nothing_happens_when_turns_the_crank)
		{
			machine.TurnCrank();
			BOOST_CHECK_EQUAL(outputStream.str(), "You turned but there's no gumballs\nNo gumball dispensed\n");
			BOOST_CHECK_EQUAL(machine.ToString(), R"text(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: 0 gumballs
Money: 0 quarters
Machine is sold out
)text");
		}

		BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()