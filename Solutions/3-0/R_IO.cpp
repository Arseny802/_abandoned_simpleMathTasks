#include "R_IO.h"

R_IO::R_IO() { }

unsigned int R_IO::ReadNumber()
{
	unsigned int result = 0;
	std::cin >> result;
	return result;
}

std::vector<unsigned int> R_IO::ReadNumbers(unsigned int count)
{
	std::vector<unsigned int> result(count);
	
	for (unsigned int iter = 0; iter < count; ++iter)
	{
		std::cin >> result[iter];
	}
	return result;
}

R_IO::~R_IO() { }
