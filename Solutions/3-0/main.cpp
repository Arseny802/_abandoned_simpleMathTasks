#include <iostream>
#include <cassert>
#include <vector>
#include <cstring>

#include "FootballTeam.h"

/* 
 * Run test or IO stream by default.
 * Make this variable 'false' to run tests.
 * */
const bool useByDefault_IO = false;
/* 
 * Enable this to run silent.
 * Program will not pause in the end.
 * */
const bool runInSilentMod = false;

const std::string testFile_1 = "../resource/test-1.txt";
const std::string testFile_2 = "../resource/test-2.txt";
const std::string testFile_3 = "../resource/test-3.txt";
const std::string testFile_4 = "../resource/test-4.txt";

inline void TestFile(std::string fileToRun = testFile_1)
{
	FootballTeam footballTeam;
	FootballPlayersTeam result;
	
	footballTeam.ReadFromFile(fileToRun);
	if (footballTeam.VerifyInput())
	{
		result = footballTeam.BuildMostEffectiveSolidaryTeam();
		
		std::cout << "Testing file '" << fileToRun << "'" << std::endl;
		std::cout << "Verifing data in file... ";
		std::cout << (footballTeam.VerifyInput() ? "Ok" : "Error") << std::endl;
		
		std::cout << "Result:   " << std::endl;
		std::cout << result;
		std::cout << "Expected: " << std::endl;
		footballTeam.PrintFileResult(fileToRun);
		std::cout << "________\n\n"; 
	}
	footballTeam.ClearData();
}

inline void RunTest()
{
	TestFile(testFile_1);
	TestFile(testFile_2);
	TestFile(testFile_3);
	TestFile(testFile_4);
}

int main(int argc, char* argv[]) 
{
	FootballTeam footballTeam;
	std::string fileName = "";
	
	std::ios_base::sync_with_stdio(false);
	
	if (argc == 1) 
	{
		if (useByDefault_IO)
		{
			footballTeam.ReadFromIO();
			if (footballTeam.VerifyInput())
			{
				std::cout << footballTeam.BuildMostEffectiveSolidaryTeam();
				std::cout << std::endl;
			}
			footballTeam.ClearData();
		}
		else
		{
			RunTest();
		}
	}
	else 
	{
		if (strcmp(argv[1], "--test") == 0) RunTest();
		else
		{
			if (strcmp(argv[1], "--file") == 0) 
			{
				if (argc == 3) fileName = argv[2];
				footballTeam.ReadFromFile(testFile_1);
			}
			else if (strcmp(argv[1], "--io") == 0) footballTeam.ReadFromIO();
			else
			{
				std::cout << "No programm input specified." << std::endl;
				system("pause");
				return 0;
			}
			
			if (footballTeam.VerifyInput())
			{
				std::cout << footballTeam.BuildMostEffectiveSolidaryTeam();
			}
			footballTeam.ClearData();
		}
	}
	if (!runInSilentMod)
	{
		std::cout << "Programm finished." << std::endl;
		system("pause");
	}
	return 0;
}