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

		std::shared_ptr<IResourceManager> res;
		Document("Zaeb writing this program without Chat GPT", res);
		ConsoleEditor console(Document, std::istream&, std::ostream&);
	}
	catch (std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
