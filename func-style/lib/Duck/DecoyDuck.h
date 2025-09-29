#ifndef DECOYDUCK_H
#define DECOYDUCK_H

#include "Behavior/IDanceBehavior.h"
#include "Behavior/IFlyBehavior.h"
#include "Behavior/IQuackBehavior.h"
#include "Duck.h"

class DecoyDuck : public Duck
{
public:
	DecoyDuck()
		: Duck(CreateFlyNoWay(), CreateDanceNoWay(), CreateMuteQuack())
	{
	}

	void Display() const override
	{
		std::cout << "I'm decoy duck!" << std::endl;
	}
};

#endif // DECOYDUCK_H