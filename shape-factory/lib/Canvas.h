#pragma once
#include "Common.h"
#include <iostream>

class ICanvas
{
public:
	virtual ~ICanvas() = default;

	virtual void SetColor(Color color) = 0;
	virtual void DrawLine(Point from, Point to) = 0;
	virtual void DrawEllipse(Point center, int horizontalRadius, int verticalRadius) = 0;
};

class SvgCanvas final : public ICanvas
{
public:
	explicit SvgCanvas(std::ostream& out)
		: m_out(out)
	{
		m_out << R"(<svg xmlns="http://www.w3.org/2000/svg" width="800" height="600">)" << std::endl;
	}

	~SvgCanvas() override
	{
		m_out << "</svg>" << std::endl;
	}

	void SetColor(Color color) override
	{
		m_currentColor = ColorToString(color);
	}

	void DrawLine(Point from, Point to) override
	{
		m_out << R"(  <line x1=")" << from.x << R"(" y1=")" << from.y
			  << R"(" x2=")" << to.x << R"(" y2=")" << to.y
			  << R"(" stroke=")" << m_currentColor << R"(" />)" << std::endl;
	}

	void DrawEllipse(Point center, int horizontalRadius, int verticalRadius) override
	{
		m_out << R"(  <ellipse cx=")" << center.x << R"(" cy=")" << center.y
			  << R"(" rx=")" << horizontalRadius << R"(" ry=")" << verticalRadius
			  << R"(" stroke=")" << m_currentColor << R"(" fill="none" />)" << std::endl;
	}

private:
	static std::string ColorToString(Color color)
	{
		switch (color)
		{
		case Color::Red:
			return "red";
		case Color::Green:
			return "green";
		case Color::Blue:
			return "blue";
		case Color::Yellow:
			return "yellow";
		case Color::Pink:
			return "pink";
		case Color::Black:
			return "black";
		}
		return "black";
	}

	std::ostream& m_out;
	std::string m_currentColor = "black";
};
