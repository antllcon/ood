#ifndef LINE_H
#define LINE_H

#include "BaseShape.h"

class Line final : public BaseShape
{
public:
	Line(const std::string& id, Color color, const std::vector<std::string>& params);
	void Draw(ICanvas* canvas) override;
	void Move(double dx, double dy) override;
	std::string GetType() const override;
	void ChangeParameters(IShape* source) override;
};

#endif // LINE_H