#ifndef IDRAWSTRATEGY_H
#define IDRAWSTRATEGY_H

#include "Circle.h"
#include "ICanvas.h"
#include "IDrawStrategy.h"
#include "IShape.h"

class CircleDrawStrategy : public IDrawStrategy
{
public:
	void Draw(ICanvas* canvas, const IShape* shape) override
	{
		auto circle = dynamic_cast<const Circle*>(shape);
		if (!circle || !canvas) return;

		canvas->SetColor(circle->GetColor());
		canvas->DrawEllipse(circle->GetCenter(), circle->GetRadius(), circle->GetRadius());
	}
};

#endif // IDRAWSTRATEGY_H