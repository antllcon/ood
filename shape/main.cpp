#include "lib/CommandProcessor.h"
#include "lib/Picture.h"
#include "lib/SvgCanvas.h"

int main()
{
	try
	{
		Picture picture;
		SvgCanvas canvas("output.svg");
		const CommandProcessor processor(picture, &canvas);

		processor.ProcessCommand("AddShape circle1 #ff0000 circle 100 100 50");
		processor.ProcessCommand("DrawShape circle1");
		processor.ProcessCommand("DrawPicture");
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}