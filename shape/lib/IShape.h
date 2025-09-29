#ifndef ISHAPE_H
#define ISHAPE_H

#include "ICanvas.h"

class IShape
{
public:
	virtual ~IShape() = default;
	virtual Color GetColor() const = 0;
	virtual void SetColor(Color color) = 0;
	virtual std::string GetId() const = 0;
	virtual std::string GetType() const = 0;
	virtual void Move(double dx, double dy) = 0;
	virtual void Draw(ICanvas* canvas) = 0;

	// TODO: доделать
	virtual void ChangeParameters(IShape* source) = 0;
};

#endif // ISHAPE_H