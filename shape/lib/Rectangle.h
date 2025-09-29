#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "BaseShape.h"

class Rectangle final : public BaseShape
{
public:
	Rectangle(const std::string& id, Color color, const std::vector<std::string>& params);
	void Draw(ICanvas* canvas) override;
	void Move(double dx, double dy) override;
	std::string GetType() const override;
	void ChangeParameters(IShape* source) override;

private:
	Point m_topLeft;
	double m_width;
	double m_height;
};

#endif // RECTANGLE_H