#ifndef RUBBERDUCK_H
#define RUBBERDUCK_H

#include "Behavior/IDanceBehavior.h"
#include "Behavior/IFlyBehavior.h"
#include "Behavior/IQuackBehavior.h"
#include "Duck.h"

class RubberDuck : public Duck
{
public:
	RubberDuck()
		: Duck(CreateFlyNoWay(), CreateSqueak(), CreateDanceNoWay())
	{
	}

	void Display() const override
	{
		std::cout << "I'm rubber duck!" << std::endl;
	}
};

#endif // RUBBERDUCK_H