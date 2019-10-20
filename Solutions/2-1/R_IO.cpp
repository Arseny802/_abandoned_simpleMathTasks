#include "R_IO.h"

R_IO::R_IO()
{
}

int R_IO::ReadNumber()
{
	int result = 0;
	std::cin >> result;
	return result;
}

std::vector<int> R_IO::ReadNumbers(unsigned int count)
{
	std::string line, token;
	std::stringstream sStream;
	std::vector<int> result(count);
	
	//std::cin >> line;
	//sStream.str(line);
	for (unsigned int iter = 0; iter < count; ++iter)
	{
		//std::getline(sStream, token, DELIMETER);
		//result[iter] = atoi(token.c_str());
		std::cin >> result[iter];
	}
	return result;
}

R_IO::~R_IO()
{
}

