#pragma once

#include "command/ICommand.h"
#include <deque>
#include <memory>

class CommandHistory final
{
	constexpr static size_t MAX_HISTORY_SIZE = 10;

public:
	CommandHistory() = default;
	~CommandHistory() = default;

	CommandHistory(const CommandHistory&) = delete;
	CommandHistory& operator=(const CommandHistory&) = delete;

	bool CanUndo() const;
	bool CanRedo() const;

	void Undo();
	void Redo();

	void AddAndExecuteCommand(std::unique_ptr<ICommand> command);

private:
	std::deque<std::unique_ptr<ICommand>> m_undoStack;
	std::deque<std::unique_ptr<ICommand>> m_redoStack;
};