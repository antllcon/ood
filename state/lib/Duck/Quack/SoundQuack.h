#ifndef QUACKBEHAVIOR_H
#define QUACKBEHAVIOR_H

#include "IQuackBehavior.h"
#include <iostream>

class SoundQuack final : public IQuackBehavior
{
public:
	void Quack() override
	{
		std::cout << "Quack Quack!" << std::endl;
	}

	bool CanQuack() const override
	{
		return true;
	}
};

#endif // QUACKBEHAVIOR_H