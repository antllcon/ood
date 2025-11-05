#include "graphics/graphics_lib.h"
#include "graphics/modern_graphics_lib.h"
#include "graphics/shape_drawing_lib.h"
#include "libs/graphics/adapter.h"

#include <cstdlib>
#include <iostream>
#pragma once

namespace app
{
void PaintPicture(shape_drawing_lib::CanvasPainter& painter)
{
	shape_drawing_lib::Triangle triangle({10, 15}, {100, 200}, {150, 250});
	shape_drawing_lib::Rectangle rectangle({30, 40}, 18, 24);

	painter.Draw(triangle);
	painter.Draw(rectangle);
}

void PaintPictureOnCanvas()
{
	graphics_lib::Canvas сanvas;
	shape_drawing_lib::CanvasPainter painter(сanvas);
	PaintPicture(painter);
}

void PaintPictureOnModernGraphicsRendererClassAdapter()
{
	ClassRendererToPainterAdapter adapter(std::cout);
	shape_drawing_lib::CanvasPainter painter(adapter);
	PaintPicture(painter);
}

} // namespace app

int main()
{
	try
	{
		std::cout << "PROGRAM ADAPTER" << std::endl;
		std::cout << "Should we use new API (y)?";

		std::string userInput;
		if (getline(std::cin, userInput) && (userInput == "y" || userInput == "Y"))
		{
			app::PaintPictureOnModernGraphicsRendererClassAdapter();
		}
		else
		{
			app::PaintPictureOnCanvas();
		}
	}
	catch (std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}
	catch (...)
	{
		std::cerr << "Unknown exception" << std::endl;
	}

	return EXIT_SUCCESS;
}
