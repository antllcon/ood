#ifndef MODELDUCK_H
#define MODELDUCK_H

#include "Behavior/IDanceBehavior.h"
#include "Behavior/IFlyBehavior.h"
#include "Behavior/IQuackBehavior.h"
#include "Duck.h"

class ModelDuck : public Duck
{
public:
	ModelDuck()
		: Duck(CreateFlyNoWay(), CreateQuack(), CreateDanceNoWay())
	{
	}

	void Display() const override
	{
		std::cout << "I'm model duck!" << std::endl;
	}
};

#endif // MODELDUCK_H