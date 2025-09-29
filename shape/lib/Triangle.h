#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "BaseShape.h"

class Triangle final : public BaseShape
{
public:
	Triangle(const std::string& id, Color color, const std::vector<std::string>& params);
	void Draw(ICanvas* canvas) override;
	void Move(double dx, double dy) override;
	std::string GetType() const override;
	void ChangeParameters(IShape* source) override;
};

#endif // TRIANGLE_H