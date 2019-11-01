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
#include "CityGraph.h"

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
    unsigned int cities_amount, iter;
    std::vector<unsigned int> renamed_towns;
    std::vector<int> tmp;
    Road tmp_road;
    double elapsed;
    CityGraph city_graph;
    RFiler filer(file_to_run);
    
    std::cout << "Testing file '" << file_to_run << "'" << std::endl;
    auto begin = std::chrono::steady_clock::now();
    
    cities_amount = filer.ReadNumber();
    city_graph.Initialize(cities_amount);
    
    for (iter = 0; iter < cities_amount - 1; ++iter)
    {
        tmp = filer.ReadNumbers(2);
        tmp_road.point_a = tmp[0];
        tmp_road.point_b = tmp[1];
        city_graph.AddRoadToFirstGraph(tmp_road);
    }
    for (iter = 0; iter < cities_amount - 1; ++iter)
    {
        tmp = filer.ReadNumbers(2);
        tmp_road.point_a = tmp[0];
        tmp_road.point_b = tmp[1];
        city_graph.AddRoadToSecondGraph(tmp_road);
    }
    
    std::cout << "Result:   " << std::endl;
    if (city_graph.CheckIsomorphic())
    {
        renamed_towns = city_graph.GetRenamedTowns();
        for (iter = 0; iter < cities_amount; ++iter)
        {
            std::cout << renamed_towns[iter] << std::endl;
        }
    }
    else
    {
        std::cout << "-1" << std::endl;
    }
    
    elapsed = std::chrono::duration_cast<std::chrono::microseconds>
        (std::chrono::steady_clock::now() - begin).count() * 0.000001;
    
    std::cout << "Expected: " << std::endl;
    filer.Read();
    filer.Close();
    
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
    CityGraph city_graph;
    ReaderIo reader_io;
    RFiler filer;
    std::string file_name;
    unsigned int number_amount, requests_amount;
    std::vector<int> numbers, requests;

    std::ios_base::sync_with_stdio(false);

    if (argc == 1)
    {
        if (kUseIoByDefault)
        {
            
            std::cout << "Result:   " << std::endl;
            
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
                
                filer.Close();
            }
            else if (strcmp(argv[1], "--io") == 0)
            {
                
            }
            else
            {
                std::cout << "No programm input specified." << std::endl;
                if (kStopConsoleProgramBeforeExit)
                {
                    std::cout << "Press enter to exit program.";
                    std::cin.get();
                }
                return 0;
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