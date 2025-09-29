#ifndef MALLARDDUCK_H
#define MALLARDDUCK_H

#include "Behavior/IDanceBehavior.h"
#include "Behavior/IFlyBehavior.h"
#include "Behavior/IQuackBehavior.h"
#include "Duck.h"

class MallardDuck : public Duck
{
public:
	MallardDuck()
		: Duck(CreateFlyWithWings(), CreateQuack(), CreateDanceWaltz())
	{
	}

	void Display() const override
	{
		std::cout << "I'm mallard duck!" << std::endl;
	}
};

#endif // MALLARDDUCK_H