#pragma once
#include "IHistory.h"

class CHistory : public IHistory
{
public:
	void Push(ICommandPtr && command) override;
	void Undo() override;
	void Redo() override;

	bool CanUndo()const override;
	bool CanRedo()const override;

private:
	std::deque<ICommandPtr> m_commands;
	size_t m_executedCommandsCount = 0;
};

