#ifndef SEQUENCE_H
#define SEQUENCE_H

#include "R_IO.h"
#include "RFiler.h"

#include <vector>

class Sequence
{
public:
	Sequence();
	~Sequence();
	
	bool VerifyInput();
	void ReadFromIO();
	void ReadFromFile(std::string fileName = "");
	void PrintFileResult(std::string fileName = "");
	void ClearData();
	std::vector<int> Calculate();
	
private:
	std::vector<int> currentSequence;
	unsigned short currentSequenceLength;
};

#endif // SEQUENCE_H
