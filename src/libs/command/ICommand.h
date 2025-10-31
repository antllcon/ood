#pragma once

class ICommand
{
public:
	virtual ~ICommand() = default;

	ICommand(const ICommand&) = delete;
	ICommand& operator=(const ICommand&) = delete;

	virtual void Execute() = 0;
	virtual void Unexecute() = 0;

	virtual bool TryToMerge(const ICommand& commandToMerge)
	{
		return false;
	}

protected:
	ICommand() = default;
};