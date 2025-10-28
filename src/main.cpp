#include <cstdlib>
#include <iostream>

int main()
{
	try
	{
		std::cout << "PROGRAM REDACTOR" << std::endl;
	}
	catch (std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
