#ifndef FLYWITHWINGS_H
#define FLYWITHWINGS_H

#include "IFlyBehavior.h"
#include <iostream>

class FlyWithWings final : public IFlyBehavior
{
public:
	void Fly() override
	{
		std::cout << "I'm flying with wings!" << std::endl;
	}
};

#endif // FLYWITHWINGS_H