#ifndef IFLYBEHAVIOR_H
#define IFLYBEHAVIOR_H

#include <functional>
#include <iostream>
#include <ostream>

using IFlyBehavior = std::function<size_t()>;

inline IFlyBehavior CreateFlyWithWings()
{
	return [flyCount = 0]() mutable -> size_t {
		flyCount++;
		std::cout << "I've been flying on wings for " << flyCount << " times already" << std::endl;
		return flyCount;
	};
}

inline IFlyBehavior CreateFlyNoWay()
{
	return []() -> size_t {
		return 0;
	};
}

#endif // IFLYBEHAVIOR_H