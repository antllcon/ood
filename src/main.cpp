#include "console/ConsoleEditor.h"
#include "document/Document.h"
#include "resource/ResourceManager.h"

#include <cstdlib>
#include <iostream>

std::shared_ptr<IResourceManager> CreateRealResourceManager()
{
	Path imagesDir = "images";
	return std::make_shared<ResourceManager>(imagesDir);
}

int main()
{
	try
	{
		std::cout << "PROGRAM REDACTOR" << std::endl;
		auto resourceManager = CreateRealResourceManager();

		auto document = std::make_unique<Document>(
			"Document",
			resourceManager);

		ConsoleEditor editor(std::move(document), std::cin, std::cout);
		editor.Run();
	}
	catch (std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}
	catch (...)
	{
		std::cerr << "CRITICAL ERROR: Unknown exception" << std::endl;
	}

	return EXIT_SUCCESS;
}
