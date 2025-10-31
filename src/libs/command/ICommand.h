#pragma once

class ICommand
{
public:
	virtual ~ICommand() = default;

	ICommand(const ICommand&) = delete;
	ICommand& operator=(const ICommand&) = delete;

	virtual void Execute()
	{
		DoExecute();
		m_isExecuted = true;
	}

	virtual void Unexecute()
	{
		DoUnexecute();
		m_isExecuted = false;
	}

	virtual bool TryToMerge(const ICommand& commandToMerge)
	{
		return false;
	}

protected:
	ICommand() = default;

	virtual void DoExecute() = 0;
	virtual void DoUnexecute() = 0;

	bool m_isExecuted = false;

};