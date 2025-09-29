#ifndef CIRCLE_H
#define CIRCLE_H

#include "BaseShape.h"

class Circle final : public BaseShape
{
public:
	Circle(const std::string& id, Color color, const std::vector<std::string>& params);
	void Draw(ICanvas* canvas) override;
	void Move(double dx, double dy) override;
	std::string GetType() const override;
	void ChangeParameters(IShape* source) override;

private:
	Point m_center;
	double m_radius;
};

#endif // CIRCLE_H