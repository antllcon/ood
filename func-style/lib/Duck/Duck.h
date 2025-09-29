#ifndef DUCK_H
#define DUCK_H

#include "Behavior/IDanceBehavior.h"
#include "Behavior/IFlyBehavior.h"
#include "Behavior/IQuackBehavior.h"

#include <cassert>
#include <functional>
#include <iostream>
#include <memory>

class Duck
{
public:
	Duck(IFlyBehavior&& flyBehavior, IQuackBehavior&& quackBehavior, IDanceBehavior&& danceBehavior)
		: m_quackBehavior(std::move(quackBehavior))
		, m_flyBehavior(std::move(flyBehavior))
		, m_danceBehavior(std::move(danceBehavior))
	{
		assert(m_quackBehavior);
		assert(m_danceBehavior);
		SetFlyBehavior(std::move(flyBehavior));
	}

	void Quack()
	{
		m_quackBehavior();
	}

	void Fly()
	{
		const size_t flyCount = m_flyBehavior();
		if (flyCount > 0 && flyCount % 2 == 0)
		{
			Quack();
		}
	}

	void Dance()
	{
		m_danceBehavior();
	}

	static void Swim()
	{
		std::cout << "I'm Swimming!" << std::endl;
	}

	void SetFlyBehavior(IFlyBehavior&& flyBehavior)
	{
		assert(flyBehavior);
		m_flyBehavior = std::move(flyBehavior);
	}

	virtual void Display() const = 0;

	virtual ~Duck() = default;

private:
	IFlyBehavior m_flyBehavior;
	IQuackBehavior m_quackBehavior;
	IDanceBehavior m_danceBehavior;
};

#endif // DUCK_H