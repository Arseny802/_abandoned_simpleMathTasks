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

/*
* Run test or IO stream by default.
* Make this variable 'false' to run tests.
* */
const bool kUseIoByDefault = true;
/*
* Stopes executing of the program in the end.
* Make 'true' to see test results.
* */
const bool kStopConsoleProgramBeforeExit = false;

const std::string kTestFileA = "../resource/test-1.txt";
const std::string kTestFileB = "../resource/test-2.txt";
const std::string kTestFileC = "../resource/test-3.txt";
const std::string kTestFileD = "../resource/test-4.txt";
const std::string kTestFileE = "../resource/test-5.txt";

#ifndef READER_IO_H
#define READER_IO_H

class ReaderIo
{
public:
    ReaderIo();
    ~ReaderIo();

    unsigned int ReadNumber();
    std::vector<int> ReadNumbers(const unsigned int amount);
};

#endif // READER_IO_H

#ifndef RFILER_H
#define RFILER_H

const char kDelimeter = ' ';

class RFiler
{
public:
    RFiler();
    explicit RFiler(std::string file_name);
    ~RFiler();

    bool Open(std::string file_name = "");
    void Close();
    void Read();
    void PrintLastString();

    bool IsFileOpened();
    unsigned int ReadNumber();
    std::vector<int> ReadNumbers(unsigned int count);

    bool SetLineNumber(unsigned int new_line_number);
    bool IncreaseLineNumber(unsigned int number_for = 1);
    bool DecreaseLineNumber(unsigned int number_for = 1);
private:
    std::ifstream current_file_stream_;
    std::string current_file_name_;
    unsigned int current_line_number_;
};

#endif // RFILER_H

RFiler::RFiler() { }

RFiler::RFiler(std::string file_name)
{
    this->current_file_name_ = file_name;
    this->current_file_stream_.open(file_name.c_str());
}

bool RFiler::Open(std::string file_name)
{
    this->current_file_name_ = file_name;
    this->current_file_stream_.open(file_name.c_str());
    return this->IsFileOpened();
}

void RFiler::Close()
{
    if (this->IsFileOpened())
    {
        this->current_file_stream_.close();
    }
}

void RFiler::Read()
{
    std::string line;

    if (this->current_file_stream_.is_open())
    {
        while (getline(this->current_file_stream_, line))
        {
            std::cout << line << '\n';
        }
        this->current_file_stream_.close();
    }
    else
    {
        std::cout << "File for reading \""
            << this->current_file_name_ << "\" is closed!\n";
    }
}

void RFiler::PrintLastString()
{
    std::string line;

    if (this->current_file_stream_.is_open())
    {
        while (getline(this->current_file_stream_, line))
        {
            //do nothing, just getting last string
        }
        std::cout << line << '\n';
        this->current_file_stream_.close();
    }
    else
    {
        std::cout << "File for reading \""
            << this->current_file_name_ << "\" is closed!\n";
    }
}

bool RFiler::IsFileOpened()
{
    return this->current_file_stream_.is_open();
}

unsigned int RFiler::ReadNumber()
{
    std::string line;
    unsigned int result = 0;

    if (this->current_file_stream_.is_open())
    {
        if (getline(this->current_file_stream_, line))
        {
            result = atoi(line.c_str());
        }
        else
        {
            std::cout << "Error occurred while file \""
                << this->current_file_name_ << "\" reading - no lines!\n";
        }
        ++this->current_line_number_;
    }
    else
    {
        std::cout << "File for reading \""
            << this->current_file_name_ << "\" is closed!\n";
    }

    return result;
}

std::vector<int> RFiler::ReadNumbers(unsigned int count)
{
    std::string line, token;
    std::stringstream string_stream;
    std::vector<int> result(count);

    if (this->current_file_stream_.is_open())
    {
        if (getline(this->current_file_stream_, line))
        {
            string_stream.str(line);
            for (unsigned int iter = 0; iter < count; ++iter)
            {
                std::getline(string_stream, token, kDelimeter);
                result[iter] = atoi(token.c_str());
            }
        }
        else
        {
            std::cout << "Error occurred while file \""
                << this->current_file_name_ << "\" reading - no lines!\n";
        }
        ++this->current_line_number_;
    }
    else
    {
        std::cout << "File for reading \""
            << this->current_file_name_ << "\" is closed!\n";
    }

    return result;
}

bool RFiler::SetLineNumber(unsigned int new_line_number)
{
    if (new_line_number > this->current_line_number_)
    {
        return this->IncreaseLineNumber(new_line_number - 
            this->current_line_number_);
    }
    else if (new_line_number < this->current_line_number_)
    {
        return this->IncreaseLineNumber(this->current_line_number_ - 
            new_line_number);
    }
    return true;
}

bool RFiler::IncreaseLineNumber(unsigned int number_for)
{
    std::string line;
    for (unsigned int iter = 0; iter < number_for; ++iter)
    {
        if (!getline(this->current_file_stream_, line))
        {
            return false;
        }
        ++this->current_line_number_;
    }
    return true;
}

bool RFiler::DecreaseLineNumber(unsigned int number_for)
{
    std::string line;
    unsigned int new_position = current_line_number_ - number_for;

    if (new_position < 0)
    {
        return false;
    }
    this->current_file_stream_.seekg(0, this->current_file_stream_.beg);

    for (unsigned int iter = 0; iter < new_position; ++iter)
    {
        if (!getline(this->current_file_stream_, line))
        {
            return false;
        }
        ++this->current_line_number_;
    }
    return true;
}

RFiler::~RFiler()
{
    if (this->IsFileOpened())
    {
        this->current_file_stream_.close();
    }
}

ReaderIo::ReaderIo() { }

unsigned int ReaderIo::ReadNumber()
{
    unsigned int result = 0;
    std::cin >> result;
    return result;
}

std::vector<int> ReaderIo::ReadNumbers(const unsigned int amount)
{
    std::vector<int> result(amount);

    for (unsigned int iter = 0; iter < amount; ++iter)
    {
        std::cin >> result[iter];
    }
    return result;
}

ReaderIo::~ReaderIo() { }



























inline void TestFile(std::string file_to_run = kTestFileA)
{
    unsigned int number_amount, requests_amount, iter;
    std::vector<int> numbers, requests;
    double elapsed;
    FixedSet fixed_set;
    RFiler filer(file_to_run);
    
    number_amount = filer.ReadNumber();
    numbers = filer.ReadNumbers(number_amount);
    requests_amount = filer.ReadNumber();
    requests = filer.ReadNumbers(requests_amount);

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
    unsigned int number_amount, requests_amount;
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
                if (kStopConsoleProgramBeforeExit)
                {
                    std::cout << "Press enter to exit program.";
                    std::cin.get();
                }
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