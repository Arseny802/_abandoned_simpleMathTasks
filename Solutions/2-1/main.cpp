#include <iostream>
#include <cassert>
#include <vector>
#include <cstring>

#include "Sequence.h"

/* 
 * Run test or IO stream by default.
 * Comment next line to run tests.
 * */
//#define DEFAULT_IO
/* 
 * Enable this to run silent.
 * Program will not pause in the end.
 * */
//#define SILENT_MOD

#define TEST_FILE_1 "../resource/test-1.txt"
#define TEST_FILE_2 "../resource/test-2.txt"
#define TEST_FILE_3 "../resource/test-3.txt"
#define TEST_FILE_4 "../resource/test-4.txt"

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