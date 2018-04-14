#include "stdafx.h"
#include "../libeditor/History.h"

class CMockCommand : public ICommand
{
public:
	CMockCommand(std::function<void()> && executeFunc, std::function<void()> && unexecuteFunc)
		: m_executeFunc(executeFunc), m_unexecuteFunc(unexecuteFunc)
	{
	}
	CMockCommand(CMockCommand const&) = default;

	void Execute()override
	{
		m_executeFunc();
	}
	void Unexecute()override
	{
		m_unexecuteFunc();
	}
private:
	std::function<void()> m_executeFunc, m_unexecuteFunc;
};

struct HistoryFixture
{
	CHistory history;
};

BOOST_FIXTURE_TEST_SUITE(History, HistoryFixture)

	BOOST_AUTO_TEST_CASE(cant_undo_with_empty_history)
	{
		BOOST_CHECK(!history.CanUndo());
		BOOST_CHECK_THROW(history.Undo(), std::runtime_error);
	}

	BOOST_AUTO_TEST_CASE(cant_redo_with_empty_history)
	{
		BOOST_CHECK(!history.CanRedo());
		BOOST_CHECK_THROW(history.Redo(), std::runtime_error);
	}

	BOOST_AUTO_TEST_CASE(can_execute_with_empty_history)
	{
		bool executed1 = false;
		bool executed2 = false;
		auto command1 = std::make_unique<CMockCommand>([&executed1]() {
			executed1 = true;
		}, []() {
			throw std::runtime_error("Test failed!");
		});

		BOOST_CHECK_NO_THROW(history.Push(std::move(command1)));
		BOOST_CHECK(executed1);
	}

	BOOST_AUTO_TEST_CASE(can_undo)
	{
		bool unexecuted1 = false;
		bool unexecuted2 = false;
		auto command1 = std::make_unique<CMockCommand>([]() {}, [&unexecuted1]() {
			unexecuted1 = true;
		});
		auto command2 = std::make_unique<CMockCommand>([]() {}, [&unexecuted2]() {
			unexecuted2 = true;
		});

		history.Push(std::move(command1));
		BOOST_CHECK(history.CanUndo());

		history.Push(std::move(command2));
		BOOST_CHECK(history.CanUndo());

		BOOST_CHECK_NO_THROW(history.Undo());
		BOOST_CHECK(unexecuted2);
		BOOST_CHECK(!unexecuted1);
		BOOST_CHECK(history.CanUndo());

		BOOST_CHECK_NO_THROW(history.Undo());
		BOOST_CHECK(unexecuted2);
		BOOST_CHECK(unexecuted1);

		BOOST_CHECK(!history.CanUndo());
	}

	BOOST_AUTO_TEST_CASE(can_redo)
	{
		bool executed1;
		bool executed2;
		auto command1 = std::make_unique<CMockCommand>([&executed1]() {
			executed1 = true;
		}, []() {});
		auto command2 = std::make_unique<CMockCommand>([&executed2]() {
			executed2 = true;
		}, []() {});

		history.Push(std::move(command1));
		BOOST_CHECK(!history.CanRedo());

		history.Push(std::move(command2));
		BOOST_CHECK(!history.CanRedo());

		executed1 = false;
		executed2 = false;

		history.Undo();
		BOOST_CHECK(history.CanRedo());
		BOOST_CHECK(!executed2);
		BOOST_CHECK(!executed1);

		history.Undo();
		BOOST_CHECK(history.CanRedo());
		BOOST_CHECK(!executed2);
		BOOST_CHECK(!executed1);

		BOOST_CHECK_NO_THROW(history.Redo());
		BOOST_CHECK(history.CanRedo());
		BOOST_CHECK(!executed2);
		BOOST_CHECK(executed1);

		BOOST_CHECK_NO_THROW(history.Redo());
		BOOST_CHECK(!history.CanRedo());
		BOOST_CHECK(executed2);
		BOOST_CHECK(executed1);

		executed1 = false;
		executed2 = false;

		history.Undo();
		BOOST_CHECK(history.CanRedo());

		BOOST_CHECK_NO_THROW(history.Redo());
		BOOST_CHECK(!history.CanRedo());
		BOOST_CHECK(executed2);
		BOOST_CHECK(!executed1);
	}

	BOOST_AUTO_TEST_CASE(can_execute_when_can_redo)
	{
		bool executed1;
		bool executed2;
		auto command1 = std::make_unique<CMockCommand>([&executed1]() {
			executed1 = true;
		}, []() {});
		auto command2 = std::make_unique<CMockCommand>([&executed2]() {
			executed2 = true;
		}, []() {});

		history.Push(std::move(command1));
		history.Undo();

		executed1 = false;
		executed2 = false;
		history.Push(std::move(command2));
		BOOST_CHECK(!executed1);
		BOOST_CHECK(executed2);
		BOOST_CHECK(!history.CanRedo());

		history.Undo();
		BOOST_CHECK(!history.CanUndo());
	}

	BOOST_AUTO_TEST_CASE(processes_failed_commands_while_execute_when_cant_redo)
	{
		bool unexecuted = false;
		auto command1 = std::make_unique<CMockCommand>([]() {}, [&unexecuted]() {
			unexecuted = true;
		});
		history.Push(std::move(command1));

		auto command2 = std::make_unique<CMockCommand>([]() {
			throw std::logic_error("Test error");
		}, []() {});
		BOOST_CHECK_THROW(history.Push(std::move(command2)), std::logic_error);

		BOOST_CHECK(!unexecuted);
		BOOST_CHECK(!history.CanRedo());
		BOOST_CHECK(history.CanUndo());

		BOOST_CHECK_NO_THROW(history.Undo());
		BOOST_CHECK(unexecuted);
	}

	BOOST_AUTO_TEST_CASE(processes_failed_commands_while_execute_when_can_redo)
	{
		bool executed;
		auto command1 = std::make_unique<CMockCommand>([&executed]() {
			executed = true;
		}, []() {});
		history.Push(std::move(command1));
		history.Undo();

		auto command2 = std::make_unique<CMockCommand>([]() {
			throw std::logic_error("Test error");
		}, []() {});

		executed = false;
		BOOST_CHECK_THROW(history.Push(std::move(command2)), std::logic_error);
		BOOST_CHECK(!history.CanUndo());
		BOOST_CHECK(history.CanRedo());
		
		BOOST_CHECK_NO_THROW(history.Redo());
		BOOST_CHECK(executed);
	}

BOOST_AUTO_TEST_SUITE_END()