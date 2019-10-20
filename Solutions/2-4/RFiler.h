#ifndef RFILER_H
#define RFILER_H

#define DELIMETER ' '

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h> /* atoi */
#include <sstream>

class RFiler
{
public:
	RFiler();
	RFiler(std::string fileName = "");
	~RFiler();
	
	bool Open(std::string fileName = "");
	void Close();
	void Read();
	void PrintLastString();
	
	bool IsFileOpened();
	int ReadNumber();
	std::vector<int> ReadNumbers(unsigned int count);
	
	bool SetLineNumber(unsigned int newLineNumber);
	bool IncreaseLineNumber(unsigned int numberFor = 1);
	bool DecreaseLineNumber(unsigned int numberFor = 1);
private:
	std::ifstream currentFileStream;
	std::string currentFileName;
	unsigned int currentLineNumber;
};

#endif // RFILER_H
