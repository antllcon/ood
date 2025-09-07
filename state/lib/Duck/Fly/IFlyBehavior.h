#ifndef IFLYBEHAVIOR_H
#define IFLYBEHAVIOR_H

#include <cstddef>

struct IFlyBehavior
{
	virtual ~IFlyBehavior() = default;
	virtual void Fly() = 0;
	virtual size_t GetFlyCount() const = 0;
};

#endif // IFLYBEHAVIOR_H