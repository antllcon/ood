#ifndef MALLARDDUCK_H
#define MALLARDDUCK_H

#include "Duck.h"
#include "Dance/DanceWaltz.h"
#include "Fly/FlyWithWings.h"
#include "Quack/SoundQuack.h"

class MallardDuck : public Duck
{
public:
	MallardDuck()
		: Duck(std::make_unique<FlyWithWings>(),
			  std::make_unique<SoundQuack>(),
			  std::make_unique<DanceWaltz>())
	{
	}

	void Display() const override
	{
		std::cout << "I'm mallard duck!" << std::endl;
	}
};

#endif // MALLARDDUCK_H