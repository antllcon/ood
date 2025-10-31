#include "console/ConsoleEditor.h"
#include "document/Document.h"
#include "resource/ResourceManager.h"

#include <cstdlib>
#include <iostream>

int main()
{
	try
	{
		std::cout << "PROGRAM REDACTOR" << std::endl;
		Path imagesDirectory = "images";

		auto resourceManager = std::make_shared<ResourceManager>(imagesDirectory);
		auto document = std::make_unique<Document>("index.html", resourceManager);
		ConsoleEditor console(std::move(document), std::cin, std::cout);

		console.Run();
	}
	catch (std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
