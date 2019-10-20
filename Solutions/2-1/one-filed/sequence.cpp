#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <stdlib.h> /* atoi */

/* 
 * Run test or IO stream by default.
 * Comment next line to run tests.
 * */
#define DEFAULT_IO
/* 
 * Enable this to run silent.
 * Program will not pause in the end.
 * */
#define SILENT_MOD

#define TEST_FILE_1 "../resource/test-1.txt"
#define TEST_FILE_2 "../resource/test-2.txt"
#define TEST_FILE_3 "../resource/test-3.txt"
#define TEST_FILE_4 "../resource/test-4.txt"

#define DELIMETER ' '

#ifndef RFILER_H
#define RFILER_H

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

#ifndef R_IO_H
#define R_IO_H

class R_IO
{
public:
	R_IO();
	~R_IO();
	
	int ReadNumber();
	std::vector<int> ReadNumbers(unsigned int count);
};

#endif // R_IO_H

RFiler::RFiler() { }

RFiler::RFiler(std::string fileName) 
{ 
	this->currentFileName = fileName;
	this->currentFileStream.open(fileName.c_str());
}

bool RFiler::Open(std::string fileName) 
{ 
	this->currentFileName = fileName;
	this->currentFileStream.open(fileName.c_str());
	return this->IsFileOpened();
}

void RFiler::Close() 
{ 
	if (this->IsFileOpened())
		this->currentFileStream.close();
}

void RFiler::Read()
{
	std::string line;
	
	if (this->currentFileStream.is_open()) 
	{
		while (getline(this->currentFileStream, line)) 
		{
			std::cout << line << '\n';
		}
		this->currentFileStream.close();
	} 
	else std::cout << "File for reading \"" << this->currentFileName << "\" is closed!\n"; 
}

void RFiler::PrintLastString()
{
	std::string line;
	
	if (this->currentFileStream.is_open()) 
	{
		while (getline(this->currentFileStream, line)) 
			continue;
		std::cout << line << '\n';
		this->currentFileStream.close();
	} 
	else std::cout << "File for reading \"" << this->currentFileName << "\" is closed!\n"; 
}

bool RFiler::IsFileOpened()
{
	return this->currentFileStream.is_open();
}

int RFiler::ReadNumber()
{
	std::string line;
	int result = 0;
	
	if (this->currentFileStream.is_open()) 
	{
		if (getline(this->currentFileStream, line)) 
		{
			result = atoi(line.c_str());
		}
		else std::cout << "Error occurred while file \"" << this->currentFileName << "\" reading - no lines!\n";
		++this->currentLineNumber;
	} 
	else std::cout << "File for reading \"" << this->currentFileName << "\" is closed!\n"; 
	
	return result;
}

std::vector<int> RFiler::ReadNumbers(unsigned int count)
{
	std::string line, token;
	std::stringstream sStream;
	std::vector<int> result(count);
	
	if (this->currentFileStream.is_open()) 
	{
		if (getline(this->currentFileStream, line)) 
		{
			sStream.str(line);
			for (unsigned int iter = 0; iter < count; ++iter)
			{
				std::getline(sStream, token, DELIMETER);
				result[iter] = atoi(token.c_str());
			}
		}
		else std::cout << "Error occurred while file \"" << this->currentFileName << "\" reading - no lines!\n";
		++this->currentLineNumber;
	} 
	else std::cout << "File for reading \"" << this->currentFileName << "\" is closed!\n";
	
	return result;
}

bool RFiler::SetLineNumber(unsigned int newLineNumber)
{
	if (newLineNumber > this->currentLineNumber)
		return this->IncreaseLineNumber(newLineNumber - this->currentLineNumber);
	else if (newLineNumber < this->currentLineNumber)
		return this->IncreaseLineNumber(this->currentLineNumber - newLineNumber);
	return true;
}

bool RFiler::IncreaseLineNumber(unsigned int numberFor)
{
	std::string line;
	for (unsigned int iter = 0; iter < numberFor; ++iter)
	{
		if (!getline(this->currentFileStream, line)) 
			return false;
		++this->currentLineNumber;
	}
	return true;
}

bool RFiler::DecreaseLineNumber(unsigned int numberFor)
{
	std::string line;
	unsigned int newPosition = currentLineNumber - numberFor;
	
	if (newPosition < 0)
		return false;
	
	this->currentFileStream.seekg (0, this->currentFileStream.beg);
	
	for (unsigned int iter = 0; iter < newPosition; ++iter)
	{
		if (!getline(this->currentFileStream, line)) 
			return false;
		++this->currentLineNumber;
	}
	return true;
}

RFiler::~RFiler() 
{ 
	if (this->IsFileOpened())
		this->currentFileStream.close();
}

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
	for (unsigned int iter = 0; iter < count; ++iter)
		std::cin >> result[iter];
	
	return result;
}

R_IO::~R_IO()
{
}

#ifndef SEQUENCE_H
#define SEQUENCE_H

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

Sequence::Sequence() { }

bool Sequence::VerifyInput()
{
	// length
	if (this->currentSequenceLength > 1000 || 
		this->currentSequenceLength == 0) return false;
	if (this->currentSequenceLength != this->currentSequence.size()) return false;
	
	// items
	for (unsigned short iter = 0; iter < this->currentSequenceLength; ++iter)
	{
		if (this->currentSequence[iter] > 1000000000 || 
			this->currentSequence[iter] < -1000000000) return false;
	}
	return true;
}

void Sequence::ReadFromIO()
{
	R_IO riostream;
	
	this->currentSequenceLength = riostream.ReadNumber();
	this->currentSequence = riostream.ReadNumbers(this->currentSequenceLength);
}

void Sequence::ReadFromFile(std::string fileName)
{
	RFiler filer(fileName);
	
	this->currentSequenceLength = filer.ReadNumber();
	this->currentSequence = filer.ReadNumbers(this->currentSequenceLength);
	
	filer.Close();
}

void Sequence::PrintFileResult(std::string fileName)
{
	RFiler filer(fileName);
	filer.PrintLastString();
	filer.Close();
}

std::vector<int> Sequence::Calculate()
{
	std::vector<int> result;
	bool moreOne, moreTwo;
	int minIndex, minValue;
	
	result.push_back(this->currentSequence[0]);
	moreOne = this->currentSequence[1] > this->currentSequence[0];
	
	for (unsigned short iter = 2; iter < this->currentSequenceLength; ++iter)
	{
		minIndex = iter - 1;
		moreTwo = this->currentSequence[iter] > this->currentSequence[minIndex];
		if (moreOne)
		{
			if (moreTwo) 
			{
				/* pushing last element */
				if (iter + 1 >= this->currentSequenceLength)
				{
					minValue = this->currentSequence[minIndex];
					while (this->currentSequence[--minIndex] < minValue)
						minValue = this->currentSequence[minIndex];
					result.push_back(this->currentSequence[minIndex + 2]);
				}
				else continue;
			}
			else
			{
				/* searching min value in increasing row*/
				minValue = this->currentSequence[minIndex--];
				while (this->currentSequence[minIndex] > this->currentSequence[iter] && 
					this->currentSequence[minIndex] > result.back())
				{
					minValue = this->currentSequence[minIndex];
					--minIndex;
				}
				result.push_back(minValue);
				moreOne = moreTwo;
				
				/* pushing last element */
				if (iter + 1 >= this->currentSequenceLength)
					result.push_back(this->currentSequence[iter]);
			}
		}
		else
		{
			if (moreTwo)
			{
				result.push_back(this->currentSequence[minIndex]);
				moreOne = moreTwo;
			}
			else continue;
		}
	}
	return result;
}

void Sequence::ClearData()
{
	this->currentSequenceLength = 0;
	this->currentSequence.clear();
}

Sequence::~Sequence()
{
	this->ClearData();
}

inline void TestFile(std::string fileToRun = TEST_FILE_1)
{
	Sequence sequence;
	std::vector<int> result;
	
	sequence.ReadFromFile(fileToRun);
	if (sequence.VerifyInput())
	{
		result = sequence.Calculate();
		
		std::cout << "Testing file '" << fileToRun << "'" << std::endl;
		std::cout << "Verifing data in file... ";
		std::cout << (sequence.VerifyInput() ? "Ok" : "Error") << std::endl;
		
		std::cout << "Result:\n\t";
		for (std::vector<int>::const_iterator iter = result.begin();iter != result.end(); ++iter)
			std::cout << *iter << ' ';
		std::cout << "\n";
		
		std::cout << "Expected:\n\t"; 
		sequence.PrintFileResult(fileToRun);
		std::cout << "________\n\n"; 
	}
	
	result.clear();
	sequence.ClearData();
}

inline void RunTest()
{
	TestFile(TEST_FILE_1);
	TestFile(TEST_FILE_2);
	TestFile(TEST_FILE_3);
	TestFile(TEST_FILE_4);
}

int main(int argc, char* argv[]) 
{
	Sequence sequence;
	std::string fileName = "";
	std::vector<int> result;
	
	if (argc == 1) 
	{
#ifdef DEFAULT_IO
		sequence.ReadFromIO();
		if (sequence.VerifyInput())
		{
			result = sequence.Calculate();
			for (std::vector<int>::const_iterator iter = result.begin(); iter != result.end(); ++iter)
				std::cout << *iter << ' ';
			std::cout << std::endl;
		}
		sequence.ClearData();
#else
		RunTest();
#endif
	}
	else 
	{
		if (strcmp(argv[1], "--test") == 0) RunTest();
		else
		{
			if (strcmp(argv[1], "--file") == 0) 
			{
				if (argc == 3) fileName = argv[2];
				sequence.ReadFromFile(TEST_FILE_1);
			}
			else if (strcmp(argv[1], "--io") == 0) sequence.ReadFromIO();
			else
			{
				std::cout << "No programm input specified." << std::endl;
				system("pause");
				return 0;
			}
			
			if (sequence.VerifyInput())
			{
				result = sequence.Calculate();
				for (std::vector<int>::const_iterator iter = result.begin(); iter != result.end(); ++iter)
					std::cout << *iter << ' ';
				std::cout << std::endl;
			}
			sequence.ClearData();
		}
	}
#ifndef SILENT_MOD
	std::cout << "Programm finished." << std::endl;
	system("pause");
#endif
	return 0;
}