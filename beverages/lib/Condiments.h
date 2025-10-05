#pragma once

#include "IBeverage.h"
#include <iostream>

enum class IceCubeType
{
	DRY,
	WATER
};

enum class SyrupType
{
	CHOCOLATE,
	MAPLE
};

enum class LiquorType
{
	CHOCOLATE,
	NUTTY
};

class CCondimentDecorator : public IBeverage
{
public:
	std::string GetDescription() const override
	{
		return m_beverage->GetDescription() + ", " + GetCondimentDescription();
	}

	double GetCost() const override
	{
		return m_beverage->GetCost() + GetCondimentCost();
	}

	virtual std::string GetCondimentDescription() const = 0;
	virtual double GetCondimentCost() const = 0;

protected:
	CCondimentDecorator(IBeveragePtr&& beverage)
		: m_beverage(move(beverage))
	{
	}

private:
	IBeveragePtr m_beverage;
};

class CCinnamon : public CCondimentDecorator
{
public:
	CCinnamon(IBeveragePtr&& beverage)
		: CCondimentDecorator(move(beverage))
	{
	}

protected:
	double GetCondimentCost() const override
	{
		return 20;
	}

	std::string GetCondimentDescription() const override
	{
		return "Cinnamon";
	}
};

class CLemon : public CCondimentDecorator
{
public:
	CLemon(IBeveragePtr&& beverage, unsigned quantity = 1)
		: CCondimentDecorator(move(beverage))
		, m_quantity(quantity)
	{
	}

protected:
	double GetCondimentCost() const override
	{
		return 10.0 * m_quantity;
	}

	std::string GetCondimentDescription() const override
	{
		return "Lemon x " + std::to_string(m_quantity);
	}

private:
	unsigned m_quantity;
};

class CIceCubes : public CCondimentDecorator
{
public:
	CIceCubes(IBeveragePtr&& beverage, unsigned quantity, IceCubeType type = IceCubeType::WATER)
		: CCondimentDecorator(move(beverage))
		, m_quantity(quantity)
		, m_type(type)
	{
	}

protected:
	double GetCondimentCost() const override
	{
		return (m_type == IceCubeType::DRY ? 10 : 5) * m_quantity;
	}

	std::string GetCondimentDescription() const override
	{
		return std::string(m_type == IceCubeType::DRY ? "Dry" : "Water") + " ice cubes x " + std::to_string(m_quantity);
	}

private:
	unsigned m_quantity;
	IceCubeType m_type;
};

class CSyrup : public CCondimentDecorator
{
public:
	CSyrup(IBeveragePtr&& beverage, SyrupType syrupType)
		: CCondimentDecorator(move(beverage))
		, m_syrupType(syrupType)
	{
	}

protected:
	double GetCondimentCost() const override
	{
		return 15;
	}

	std::string GetCondimentDescription() const override
	{
		return std::string(m_syrupType == SyrupType::CHOCOLATE ? "Chocolate" : "Maple") + " syrup";
	}

private:
	SyrupType m_syrupType;
};

class CChocolateCrumbs : public CCondimentDecorator
{
public:
	CChocolateCrumbs(IBeveragePtr&& beverage, unsigned mass)
		: CCondimentDecorator(move(beverage))
		, m_mass(mass)
	{
	}

	double GetCondimentCost() const override
	{
		return 2.0 * m_mass;
	}

	std::string GetCondimentDescription() const override
	{
		return "Chocolate crumbs " + std::to_string(m_mass) + "g";
	}

private:
	unsigned m_mass;
};

class CCoconutFlakes : public CCondimentDecorator
{
public:
	CCoconutFlakes(IBeveragePtr&& beverage, unsigned mass)
		: CCondimentDecorator(move(beverage))
		, m_mass(mass)
	{
	}

protected:
	double GetCondimentCost() const override
	{
		return 1.0 * m_mass;
	}
	std::string GetCondimentDescription() const override
	{
		return "Coconut flakes " + std::to_string(m_mass) + "g";
	}

private:
	unsigned m_mass;
};

class CCream final : public CCondimentDecorator
{
public:
	explicit CCream(IBeveragePtr&& beverage)
		: CCondimentDecorator(move(beverage))
	{
	}

protected:
	double GetCondimentCost() const override
	{
		return 25;
	}

	std::string GetCondimentDescription() const override
	{
		return "Cream";
	}
};

class CChocolate final : public CCondimentDecorator
{
public:
	explicit CChocolate(IBeveragePtr&& beverage, const unsigned pieces)
		: CCondimentDecorator(move(beverage))
	{
		if (pieces > MAX_PIECES)
		{
			throw std::invalid_argument("Invalid pieces count (max pieces: " + std::to_string(MAX_PIECES));
		}

		m_pieces = pieces;
	}

protected:
	double GetCondimentCost() const override
	{
		return m_pieces * 10;
	}

	std::string GetCondimentDescription() const override
	{
		return "Chocolate pieces x " + std::to_string(m_pieces);
	}

private:
	const unsigned MAX_PIECES = 5;

	unsigned m_pieces;
};

class CLiquor final : public CCondimentDecorator
{
public:
	CLiquor(IBeveragePtr&& beverage, const LiquorType liquorType)
		: CCondimentDecorator(std::move(beverage))
		, m_liquorType(liquorType)
	{
	}

protected:
	double GetCondimentCost() const override
	{
		return 50;
	}

	std::string GetCondimentDescription() const override
	{
		return std::string(m_liquorType == LiquorType::CHOCOLATE ? "Chocolate" : "Nutty") + " Liquor";
	}

private:
	LiquorType m_liquorType;
};
