#ifndef DUCK_H
#define DUCK_H

#include "Fly/IFlyBehavior.h"
#include "Quack/IQuackBehavior.h"
#include "Dance/IDanceBehavior.h"

#include <cassert>
#include <iostream>
#include <memory>

class Duck
{
public:
	Duck(std::unique_ptr<IFlyBehavior>&& flyBehavior,
		std::unique_ptr<IQuackBehavior>&& quaсkBehavior,
		std::unique_ptr<IDanceBehavior>&& danceBehavior)
		: m_quackBehavior(std::move(quaсkBehavior))
		, m_danceBehavior(std::move(danceBehavior))
	{
		assert(m_quackBehavior);
		assert(m_danceBehavior);
		SetFlyBehavior(std::move(flyBehavior));
	}

	void Quack()
	{
		m_quackBehavior->Quack();
	}

	void Fly()
	{
		m_flyBehavior->Fly();
	}

	void Dance()
	{
		m_danceBehavior->Dance();
	}

	static void Swim()
	{
		std::cout << "I'm Swimming!" << std::endl;
	}

	void SetFlyBehavior(std::unique_ptr<IFlyBehavior>&& flyBehavior)
	{
		assert(flyBehavior);
		m_flyBehavior = std::move(flyBehavior);
	}

	virtual void Display() const = 0;

	virtual ~Duck() = default;

private:
	std::unique_ptr<IFlyBehavior> m_flyBehavior;
	std::unique_ptr<IQuackBehavior> m_quackBehavior;
	std::unique_ptr<IDanceBehavior> m_danceBehavior;
};

#endif // DUCK_H