#ifndef IFLYBEHAVIOR_H
#define IFLYBEHAVIOR_H

struct IFlyBehavior
{
	virtual ~IFlyBehavior() = default;
	virtual void Fly() = 0;
};

#endif // IFLYBEHAVIOR_H