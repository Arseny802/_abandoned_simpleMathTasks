#ifndef R_IO_H
#define R_IO_H

#include <iostream>
#include <vector>

class R_IO
{
public:
	R_IO();
	~R_IO();
	
	unsigned int ReadNumber();
	std::vector<unsigned int> ReadNumbers(unsigned int count);
};

#endif // R_IO_H
