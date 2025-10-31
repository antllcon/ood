#include "CommandHistory.h"

bool CommandHistory::CanUndo() const
{
	return !m_undoStack.empty();
}

bool CommandHistory::CanRedo() const
{
	return !m_redoStack.empty();
}

void CommandHistory::Undo()
{
	if (!CanUndo())
	{
		return;
	}

	auto command = std::move(m_undoStack.back());
	m_undoStack.pop_back();

	command->Unexecute();

	m_redoStack.push_back(std::move(command));
}

void CommandHistory::Redo()
{
	if (!CanRedo())
	{
		return;
	}

	auto command = std::move(m_redoStack.back());
	m_redoStack.pop_back();

	command->Execute();

	m_undoStack.push_back(std::move(command));
}

void CommandHistory::AddAndExecuteCommand(std::unique_ptr<ICommand> command)
{
	command->Execute();

	if (!m_undoStack.empty() && m_redoStack.empty())
	{
		auto& lastCommand = m_undoStack.back();
		if (lastCommand->TryToMerge(*command))
		{
			return;
		}
	}

	m_redoStack.clear();

	m_undoStack.push_back(std::move(command));
	if (m_undoStack.size() > MAX_HISTORY_SIZE)
	{
		m_undoStack.pop_front();
	}
}