#ifndef SQUEAKBEHAVIOR_H
#define SQUEAKBEHAVIOR_H

#include "IQuackBehavior.h"
#include <iostream>

class SoundSqueak final : public IQuackBehavior
{
public:
	void Quack() override
	{
		std::cout << "Squeak!" << std::endl;
	}
};

#endif // SQUEAKBEHAVIOR_H