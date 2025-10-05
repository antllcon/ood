#pragma once

#include "IBeverage.h"

enum class TeaSort
{
	NURRI = 1,
	SELENA,
	CEYLON,
	STEPAN
};

enum class MilkshakeSize
{
	SMALL = 1,
	MEDIUM,
	LARGE,
};

std::string GetStringNameOfTeaSort(const TeaSort sort)
{
	switch (sort)
	{
	case TeaSort::NURRI:
		return "Nurri Tea";
	case TeaSort::SELENA:
		return "Selena Tea";
	case TeaSort::CEYLON:
		return "Ceylon Tea";
	case TeaSort::STEPAN:
		return "Stepan Tea";
	default:
		return "Nasvai Tea";
	}
}

std::string GetStringSizeOfMilkshake(const MilkshakeSize size)
{
	switch (size)
	{
	case MilkshakeSize::SMALL:
		return "Small Milkshake";
	case MilkshakeSize::MEDIUM:
		return "Medium Milkshake";
	case MilkshakeSize::LARGE:
		return "Large Milkshake";
	default:
		return "Normal Milkshake";
	}
}

class CBeverage : public IBeverage
{
public:
	explicit CBeverage(std::string description)
		: m_description(std::move(description))
	{
	}

	std::string GetDescription() const override final
	{
		return m_description;
	}

private:
	std::string m_description;
};

class CCoffee : public CBeverage
{
public:
	explicit CCoffee(const std::string& description = "Coffee")
		: CBeverage(description)
	{
	}

	double GetCost() const override
	{
		return 60;
	}
};

class CCappuccino : public CCoffee
{
public:
	explicit CCappuccino(bool isDouble = false)
		: CCoffee(isDouble ? "Double Cappuccino" : "Default Cappuccino")
		, m_isDouble(isDouble)
	{
	}

	double GetCost() const override
	{
		return (m_isDouble ? 120 : 80);
	}

private:
	bool m_isDouble;
};

class CLatte : public CCoffee
{
public:
	explicit CLatte(bool isDouble = false)
		: CCoffee(isDouble ? "Double Latte" : "Standard Latte")
		, m_isDouble(isDouble)
	{
	}

	double GetCost() const override
	{
		return (m_isDouble ? 130 : 90);
	}

private:
	bool m_isDouble;
};

class CTea : public CBeverage
{
public:
	explicit CTea(const TeaSort sort = TeaSort::STEPAN)
		: CBeverage(GetStringNameOfTeaSort(sort))
	{
	}

	double GetCost() const override
	{
		return 30;
	}
};

class CMilkshake : public CBeverage
{
public:
	explicit CMilkshake(const MilkshakeSize size = MilkshakeSize::LARGE)
		: CBeverage(GetStringSizeOfMilkshake(size))
		, m_size(size)
	{
	}

	double GetCost() const override
	{
		switch (m_size)
		{
		case MilkshakeSize::SMALL:
			return 50;
		case MilkshakeSize::MEDIUM:
			return 60;
		case MilkshakeSize::LARGE:
			return 80;
		default:
			return 80;
		}
	}

private:
	MilkshakeSize m_size;
};
