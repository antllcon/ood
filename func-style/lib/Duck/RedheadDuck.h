#ifndef REDHEADDUCK_H
#define REDHEADDUCK_H

#include "Behavior/IDanceBehavior.h"
#include "Behavior/IFlyBehavior.h"
#include "Behavior/IQuackBehavior.h"
#include "Duck.h"

class RedheadDuck : public Duck
{
public:
	RedheadDuck()
		: Duck(CreateFlyWithWings(), CreateQuack(), CreateDanceMinuet())
	{
	}

	void Display() const override
	{
		std::cout << "I'm redhead duck!" << std::endl;
	}
};

#endif // REDHEADDUCK_H