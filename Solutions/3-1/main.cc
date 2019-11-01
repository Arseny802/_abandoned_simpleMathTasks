#include <iostream>  /* console "reading" */
#include <fstream>   /* file reading */
#include <cstring>   /* strncmp() */
#include <sstream>   /* parse string of integers */
#include <stdlib.h>  /* atoi */
#include <chrono>    /* test proccess time elapsed */
#include <algorithm>
#include <vector>
#include <string>
#include <random>

#include "ReaderIo.h"
#include "RFiler.h"
#include "FixedSet.h"

/*
* Run test or IO stream by default.
* Make this variable 'false' to run tests.
* */
const bool kUseIoByDefault = false;
/*
* Stopes executing of the program in the end.
* Make 'true' to see test results.
* */
const bool kStopConsoleProgramBeforeExit = true;

const std::string kTestFileA = "../resource/test-1.txt";
const std::string kTestFileB = "../resource/test-2.txt";
const std::string kTestFileC = "../resource/test-3.txt";
const std::string kTestFileD = "../resource/test-4.txt";

inline void TestFile(std::string file_to_run = kTestFileA)
{
    unsigned int iter;
    double elapsed;
    FixedSet fixed_set;
    RFiler filer(file_to_run);
    
    unsigned int number_amount = filer.ReadNumber();
    std::vector<int> numbers = filer.ReadNumbers(number_amount);
    unsigned int requests_amount = filer.ReadNumber();
    std::vector<int> requests = filer.ReadNumbers(requests_amount);

    std::cout << "Testing file '" << file_to_run << "'" << std::endl;
    auto begin = std::chrono::steady_clock::now();
    
    fixed_set.Initialize(numbers);
    std::cout << "Result:   " << std::endl;
    for (iter = 0; iter < requests_amount; ++iter)
    {
        if (fixed_set.Contains(requests[iter]))
        {
            std::cout << "Yes" << std::endl;
        }
        else
        {
            std::cout << "No" << std::endl;
        }
    }
    
    elapsed = std::chrono::duration_cast<std::chrono::microseconds>
        (std::chrono::steady_clock::now() - begin).count() * 0.000001;
    
    std::cout << "Expected: " << std::endl;
    filer.Read();
    filer.Close();
    
    for (iter = 0; iter < number_amount; ++iter)
    {
        if (!fixed_set.Contains(numbers[iter]))
        {
            std::cout << "Error!" << std::endl;
            std::cout << "Item " << iter << " not found in set." << std::endl;
            std::cout << "Item's value: " << numbers[iter] << std::endl;
        }
    }
    numbers.clear();
    requests.clear();
    
    std::cout << "Proccess finished in " << elapsed << " seconds." << std::endl;
}

inline void RunTest()
{
    TestFile(kTestFileA);
    TestFile(kTestFileB);
    TestFile(kTestFileC);
    TestFile(kTestFileD);
}

int main(int argc, char* argv[])
{
    FixedSet fixed_set;
    ReaderIo reader_io;
    RFiler filer;
    std::string file_name;
    int number_amount, requests_amount;
    std::vector<int> numbers, requests;

    std::ios_base::sync_with_stdio(false);

    if (argc == 1)
    {
        if (kUseIoByDefault)
        {
            number_amount = reader_io.ReadNumber();
            numbers = reader_io.ReadNumbers(number_amount);
            requests_amount = reader_io.ReadNumber();
            requests = reader_io.ReadNumbers(requests_amount);
            fixed_set.Initialize(numbers);
            std::cout << "Result:   " << std::endl;
            for (unsigned int iter = 0; iter < requests_amount; ++iter)
            {
                if (fixed_set.Contains(requests[iter]))
                {
                    std::cout << "Yes" << std::endl;
                }
                else
                {
                    std::cout << "No" << std::endl;
                }
            }
        }
        else
        {
            RunTest();
        }
    }
    else
    {
        if (strcmp(argv[1], "--test") == 0)
        {
            RunTest();
        }
        else
        {
            if (strcmp(argv[1], "--file") == 0)
            {
                if (argc == 3)
                {
                    file_name = argv[2];
                }
                else
                {
                    file_name = kTestFileA;
                }
                filer.Open(file_name);
                number_amount = filer.ReadNumber();
                numbers = filer.ReadNumbers(number_amount);
                requests_amount = filer.ReadNumber();
                requests = filer.ReadNumbers(requests_amount);
                filer.Close();
            }
            else if (strcmp(argv[1], "--io") == 0)
            {
                number_amount = reader_io.ReadNumber();
                numbers = reader_io.ReadNumbers(number_amount);
                requests_amount = reader_io.ReadNumber();
                requests = reader_io.ReadNumbers(requests_amount);
            }
            else
            {
                std::cout << "No programm input specified." << std::endl;
                system("pause");
                return 0;
            }
            
            fixed_set.Initialize(numbers);
            for (unsigned int iter = 0; iter < requests_amount; ++iter)
            {
                if (fixed_set.Contains(requests[iter]))
                {
                    std::cout << "Yes" << std::endl;
                }
                else
                {
                    std::cout << "No" << std::endl;
                }
            }
        }
    }
    if (kStopConsoleProgramBeforeExit)
    {
        std::cout << "Press enter to exit program.";
        std::cin.get();
    }
    return 0;
}