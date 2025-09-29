#ifndef TEXTSHAPE_H
#define TEXTSHAPE_H

#include "BaseShape.h"

class TextShape final : public BaseShape
{
public:
	TextShape(const std::string& id, Color color, const std::vector<std::string>& params);
	void Draw(ICanvas* canvas) override;
	void Move(double dx, double dy) override;
	std::string GetType() const override;
	void ChangeParameters(IShape* source) override;
};

#endif // TEXTSHAPE_H