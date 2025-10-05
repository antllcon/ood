#pragma once

#include <cmath>
#include <limits>

#define M_PI 3.14159265358979323846

class CWindDirectionCounter final
{
public:
	void Update(double directionDegrees)
	{
		m_directions.push_back(directionDegrees);
	}

	double GetAverage() const
	{
		if (m_directions.empty())
		{
			return 0;
		}

		double sumX = 0;
		double sumY = 0;

		for (const auto angle : m_directions)
		{
			double rad = angle * M_PI / 180.0;
			sumX += std::cos(rad);
			sumY += std::sin(rad);
		}

		double avgX = sumX / m_directions.size();
		double avgY = sumY / m_directions.size();

		double avgRad = std::atan2(avgY, avgX);
		double avgDeg = avgRad * 180.0 / M_PI;

		if (avgDeg < 0)
		{
			avgDeg += 360.0;
		}

		return avgDeg;
	}

	double GetMin() const
	{
		if (m_directions.empty()) return 0;

		double min = m_directions[0];
		for (double angle : m_directions)
		{
			if (angle < min) min = angle;
		}
		return min;
	}

	double GetMax() const
	{
		if (m_directions.empty()) return 0;

		double max = m_directions[0];
		for (double angle : m_directions)
		{
			if (angle > max) max = angle;
		}
		return max;
	}

	void Reset()
	{
		m_directions.clear();
	}

private:
	std::vector<double> m_directions;
};

class CStatsCounter final
{
public:
	void Update(double value)
	{
		if (m_min > value)
		{
			m_min = value;
		}

		if (m_max < value)
		{
			m_max = value;
		}

		m_acc += value;
		++m_count;
	}

	double GetMin() const
	{
		return m_min;
	}

	double GetMax() const
	{
		return m_max;
	}

	double GetAverage() const
	{
		if (m_count != 0)
		{
			return m_acc / m_count;
		}

		return 0;
	}

private:
	double m_min = std::numeric_limits<double>::infinity();
	double m_max = -std::numeric_limits<double>::infinity();
	double m_acc = 0;
	unsigned m_count = 0;
};
