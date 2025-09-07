#ifndef RUBBERDUCK_H
#define RUBBERDUCK_H

#include "Quack/SoundSqueak.h"

class RubberDuck : public Duck
{
public:
	RubberDuck()
		: Duck(std::make_unique<FlyNoWay>(),
			  std::make_unique<SoundSqueak>(),
			  std::make_unique<DanceNoWay>())
	{
	}

	void Display() const override
	{
		std::cout << "I'm rubber duck!" << std::endl;
	}
};

#endif // RUBBERDUCK_H