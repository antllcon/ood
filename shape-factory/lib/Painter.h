#pragma once
#include <PictureDraft.h>

class Painter
{
public:
	void DrawPicture(const IPictureDraft& draft, ICanvas& canvas) const
	{
		for (size_t i = 0; i < draft.GetShapeCount(); ++i)
		{
			const Shape& shape = draft.GetShape(i);
			shape.Draw(canvas);
		}
	}
};
