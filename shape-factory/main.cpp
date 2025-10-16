#include <ShapeFactory.h>
#include <exception>
#include <iostream>

int main()
{
	try
	{
		ShapeFactory factory;
		Designer designer(factory);
		Painter painter;

		std::stringstream inputStream;
		inputStream << "ellipse yellow 600 100 50 50\n";		 // Солнце
		inputStream << "rectangle blue 100 300 300 500\n";		 // Корпус дома
		inputStream << "triangle red 100 300 300 300 200 150\n"; // Крыша
		inputStream << "rectangle black 180 400 220 500\n";		 // Дверь
		inputStream << "ellipse green 400 450 150 50\n";		 // Газон

		std::cout << "Reading shape descriptions..." << std::endl;

		std::unique_ptr<IPictureDraft> draft = designer.CreateDraft(inputStream);
		std::cout << "Picture draft created with " << draft->GetShapeCount() << " shapes" << std::endl;

		std::ofstream outputFile("picture.svg");
		if (!outputFile)
		{
			throw std::runtime_error("Failed to open output file picture.svg");
		}

		SvgCanvas canvas(outputFile);
		std::cout << "Painter is drawing the picture to picture.svg..." << std::endl;

		painter.DrawPicture(*draft, canvas);
		std::cout << "Done! Please open picture.svg to see the result." << std::endl;
	}
	catch (std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
