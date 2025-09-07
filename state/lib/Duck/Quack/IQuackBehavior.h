#ifndef IQUAKBEHAVIOR_H
#define IQUAKBEHAVIOR_H

struct IQuackBehavior
{
	virtual ~IQuackBehavior() = default;
	virtual void Quack() = 0;
	virtual bool CanQuack() const = 0;
};

#endif // IQUAKBEHAVIOR_H