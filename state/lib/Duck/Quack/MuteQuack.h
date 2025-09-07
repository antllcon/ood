#ifndef MUTEQUAKBEHAVIOR_H
#define MUTEQUAKBEHAVIOR_H

#include "IQuackBehavior.h"

class MuteQuack final : public IQuackBehavior
{
public:
	void Quack() override
	{
	}

	bool CanQuack() const override
	{
		return false;
	}
};

#endif // MUTEQUAKBEHAVIOR_H