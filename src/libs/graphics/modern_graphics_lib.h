#pragma once
#include <boost/format.hpp>

namespace modern_graphics_lib
{
class Point
{
public:
	Point(int x, int y)
		: x(x)
		, y(y)
	{
	}
	int x;
	int y;
};

class ModernGraphicsRenderer
{
public:
	explicit ModernGraphicsRenderer(std::ostream& strm)
		: m_out(strm)
	{
	}

	~ModernGraphicsRenderer()
	{
		if (m_drawing)
		{
			EndDraw();
		}
	}

	void BeginDraw()
	{
		if (m_drawing)
		{
			throw std::logic_error("Drawing has already begun");
		}

		m_out << "<draw>" << std::endl;
		m_drawing = true;
	}

	void DrawLine(const Point& start, const Point& end)
	{
		if (!m_drawing)
		{
			throw std::logic_error("DrawLine is allowed between BeginDraw()/EndDraw() only");
		}
		m_out << boost::format(R"(  <line fromX="%1%" fromY="%2%" toX="%3%" toY="%4%"/>)")
				% start.x % start.y % end.x % end.y
			  << std::endl;
	}

	void EndDraw()
	{
		if (!m_drawing)
		{
			throw std::logic_error("Drawing has not been started");
		}
		m_out << "</draw>" << std::endl;
		m_drawing = false;
	}

private:
	std::ostream& m_out;
	bool m_drawing = false;
};
} // namespace modern_graphics_lib