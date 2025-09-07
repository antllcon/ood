#ifndef FLYWITHWINGS_H
#define FLYWITHWINGS_H

#include "IFlyBehavior.h"
#include <iostream>

class FlyWithWings final : public IFlyBehavior
{
public:
	size_t GetFlyCount() const override
	{
		return m_flyCount;
	}

	void Fly() override
	{
		m_flyCount++;
		std::cout << "I've been flying on wings for " << m_flyCount << " times already" << std::endl;
	}

private:
	size_t m_flyCount = 0;
};

#endif // FLYWITHWINGS_H