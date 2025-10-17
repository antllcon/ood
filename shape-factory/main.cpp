#include "Designer.h"

#include <ShapeFactory.h>
#include <exception>
#include <fstream>
#include <iostream>

int main()
{
	try
	{
		ShapeFactory factory;
		Designer designer(factory);
		Painter painter;

		std::ifstream inputFile("commands.txt");
		std::unique_ptr<IPictureDraft> draft = designer.CreateDraft(inputFile);
		std::cout << "Picture has: " << draft->GetShapeCount() << " shapes" << std::endl;

		std::ofstream outputFile("picture.svg");
		SvgCanvas canvas(outputFile);
		painter.DrawPicture(*draft, canvas);
	}
	catch (std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
