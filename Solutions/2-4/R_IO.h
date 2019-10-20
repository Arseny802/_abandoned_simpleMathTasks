#ifndef R_IO_H
#define R_IO_H

#define DELIMETER ' '

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stdlib.h> /* atoi */

class R_IO
{
public:
	R_IO();
	~R_IO();
	
	int ReadNumber();
	std::vector<int> ReadNumbers(unsigned int count);
};

#endif // R_IO_H
