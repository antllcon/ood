#ifndef DUCKFUNCTIONS_H
#define DUCKFUNCTIONS_H

#include "Duck/Duck.h"

inline void DrawDuck(Duck const& duck)
{
	duck.Display();
}

inline void PlayWithDuck(Duck& duck)
{
	DrawDuck(duck);
	duck.Quack();
	duck.Fly();
	duck.Dance();
	std::cout << std::endl;
}

inline void DropDuckFromFloor(Duck& duck, const size_t numberFloor)
{
	std::cout << "Flew from the " << numberFloor << " floor..." << std::endl;

	for (size_t i = 0; i < numberFloor; ++i)
	{
		duck.Fly();
	}

	std::cout << std::endl;
}

#endif // DUCKFUNCTIONS_H