#ifndef REDHEADDUCK_H
#define REDHEADDUCK_H

#include "Dance/DanceMinuet.h"

class RedheadDuck : public Duck
{
public:
	RedheadDuck()
		: Duck(std::make_unique<FlyWithWings>(),
			  std::make_unique<SoundQuack>(),
			  std::make_unique<DanceMinuet>())
	{
	}

	void Display() const override
	{
		std::cout << "I'm redhead duck!" << std::endl;
	}
};

#endif // REDHEADDUCK_H