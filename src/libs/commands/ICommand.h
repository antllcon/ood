#pragma once

// TODO: где писать код для склеивания команд? Должно ли это относиться к этому классу?
class ICommand
{
public:
	virtual ~ICommand() = default;

	virtual void Execute() = 0;
	virtual void Unexecute() = 0;
};