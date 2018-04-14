#pragma once
#include "ICommand.h"

class CHistory
{
	typedef std::unique_ptr<ICommand> ICommandPtr;

public:
	void Push(ICommandPtr && command);
	void Undo();
	void Redo();

	bool CanUndo()const;
	bool CanRedo()const;

private:
	std::deque<ICommandPtr> m_commands;
	size_t m_executedCommandsCount = 0;
};

