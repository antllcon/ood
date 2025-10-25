#include "processStream/ProcessStream.h"

#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
	try
	{
		ProcessStream::ProcessTransform(argc, argv);
		return EXIT_SUCCESS;
	}
	catch (const std::ios_base::failure& e)
	{
		std::cerr << "I/O Error: " << e.what() << std::endl;
	}
	catch (const std::invalid_argument& e)
	{
		std::cerr << "Argument Error: " << e.what() << std::endl;
	}
	catch (const std::logic_error& e)
	{
		std::cerr << "Logic Error: " << e.what() << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}

	return EXIT_FAILURE;
}