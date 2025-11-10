#pragma once
#include <boost/format.hpp>
#include <iomanip>

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

class RGBAColor
{
public:
	RGBAColor(float r, float g, float b, float a)
		: r(r)
		, g(g)
		, b(b)
		, a(a)
	{
	}
	float r, g, b, a;
};

class ModernGraphicsRenderer
{
public:
	explicit ModernGraphicsRenderer(std::ostream& strm)
		: m_out(strm)
		, m_defaultStreamFlags(strm.flags())
	{
	}

	~ModernGraphicsRenderer()
	{
		if (m_drawing)
		{
			EndDraw();
		}
		m_out.flags(m_defaultStreamFlags);
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

	void DrawLine(const Point& start, const Point& end, const RGBAColor& color)
	{
		if (!m_drawing)
		{
			throw std::logic_error("DrawLine is allowed between BeginDraw()/EndDraw() only");
		}

		m_out << std::fixed << std::setprecision(2);
		m_out << (boost::format(R"(  <line fromX="%1%" fromY="%2%" toX="%3%" toY="%4%">\n    <color r="%5%" g="%6%" b="%7%" a="%8%"/>\n  </line>\n)")
			% start.x % start.y % end.x % end.y % color.r % color.g % color.b % color.a);
		m_out.copyfmt(std::ios(nullptr));
		m_out.flags(m_defaultStreamFlags);
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
	std::ios_base::fmtflags m_defaultStreamFlags;
};
} // namespace modern_graphics_lib