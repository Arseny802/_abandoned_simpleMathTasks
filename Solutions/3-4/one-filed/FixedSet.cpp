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

#ifndef FIXEDSET_H
#define FIXEDSET_H

struct HashTableRow 
{
public:
    int table_length;
    int coefficient_a;
    int coefficient_b;
    std::vector<int> values;
};

// 2*10^9 by the task
const int kMaxInputInteger = 0x77359400;

class FixedSet
{
public:
    FixedSet();
    void Initialize(const std::vector<int>& numbers);
    bool Contains(int number) const;
    
private:
    int fixed_set_size_;
    int hash_function_coefficient_a_;
    int hash_function_coefficient_b_;
    int hash_function_coefficient_p_;
    std::vector<HashTableRow> fixed_set_;
    std::mt19937 mersenne_twister_;
    
    bool IsPrimeNumber(const int number);
    int GetNextPrimeNumber(const int number);
    
    void InitializeHashTableRows(std::vector<int> numbers);
    int GetHashFromKey(int key) const;
    int GetHashFromRowAndKey(HashTableRow row, int key) const;
};

#endif // FIXEDSET_H

FixedSet::FixedSet()
{
    this->mersenne_twister_ = std::mt19937(time(0));
}

bool FixedSet::IsPrimeNumber(const int number) 
{
    int iter;
    
    for (iter = 2; iter * iter <= number; ++iter)
    {
        if (number % iter == 0) 
        {
            return false;
        }
    }
    return true;
}

int FixedSet::GetNextPrimeNumber(const int number) 
{
    int iter = number + 1;
    for( ; !this->IsPrimeNumber(iter); ++iter);
    return iter;
}

int FixedSet::GetHashFromKey(const int key) const
{
    if (this->hash_function_coefficient_p_ == 0 || this->fixed_set_size_ == 0)
    {
        return 0;
    }
    return std::abs((hash_function_coefficient_a_ * key + 
        hash_function_coefficient_b_) % hash_function_coefficient_p_) 
        % this->fixed_set_size_;
}

int FixedSet::GetHashFromRowAndKey(HashTableRow row, int key) const
{
    if (this->hash_function_coefficient_p_ == 0 || row.table_length == 0)
    {
        return 0;
    }
    return std::abs((row.coefficient_a * key + row.coefficient_b) 
        % hash_function_coefficient_p_) % row.table_length;
}

void FixedSet::InitializeHashTableRows(std::vector<int> numbers) 
{
    int iter, sub_iter, row;
    bool collision_found;
    std::vector<int> items_to_write, items_hashes;
    
    for (iter = 0; iter < this->fixed_set_size_; ++iter) 
    {
        this->fixed_set_[iter].table_length = 0;
    }
        
    for (iter = 0; iter < this->fixed_set_size_; ++iter)
    {
        ++this->fixed_set_[this->GetHashFromKey(numbers[iter])].table_length;
    }
    
    for (iter = 0; iter < this->fixed_set_size_; ++iter) 
    {
        if (this->fixed_set_[iter].table_length) 
        {
            this->fixed_set_[iter].table_length *= 
                this->fixed_set_[iter].table_length;
            this->fixed_set_[iter].values.resize
                (this->fixed_set_[iter].table_length);
            
            if (this->fixed_set_[iter].table_length == 1) 
            {
                this->fixed_set_[iter].coefficient_a = 0;
                this->fixed_set_[iter].coefficient_b = 0;
                for (sub_iter = 0; sub_iter < this->fixed_set_size_; ++sub_iter)
                {
                    if (iter == this->GetHashFromKey(numbers[sub_iter]))
                    {
                        this->fixed_set_[iter].values[0] = numbers[sub_iter];
                    }
                }
            }
            else
            {
                for (sub_iter = 0; sub_iter < this->fixed_set_size_; ++sub_iter)
                {
                    if (iter == this->GetHashFromKey(numbers[sub_iter]))
                    {
                        items_to_write.push_back(numbers[sub_iter]);
                    }
                }
                do
                {
                    collision_found = false;
                    std::uniform_int_distribution<> randomize_a
                        (1, this->hash_function_coefficient_p_);
                    std::uniform_int_distribution<> randomize_b
                        (0, this->hash_function_coefficient_p_);
                    this->fixed_set_[iter].coefficient_a = 
                        randomize_a(mersenne_twister_);
                    this->fixed_set_[iter].coefficient_b = 
                        randomize_b(mersenne_twister_);
                    
                    for (auto &tmp_item : items_to_write)
                    {
                        row = this->GetHashFromRowAndKey
                            (this->fixed_set_[iter], tmp_item);
                        
                        for (auto &created_item_hash : items_hashes)
                        {
                            if (created_item_hash == row)
                            {
                                collision_found = true;
                                break;
                            }
                        }
                        if (collision_found)
                        {
                            break;
                        }
                        items_hashes.push_back(row);
                    }
                    items_hashes.clear();
                } while (collision_found);
                
                for (auto &tmp_item : items_to_write)
                {
                    row = this->GetHashFromRowAndKey
                        (this->fixed_set_[iter], tmp_item);
                    this->fixed_set_[iter].values[row] = tmp_item;
                }
                items_to_write.clear();
            }
        }
    }
}

void FixedSet::Initialize(const std::vector<int>& numbers)
{
    this->fixed_set_size_ = numbers.size();
    this->fixed_set_.resize(this->fixed_set_size_);
    
    this->hash_function_coefficient_p_ = 
        this->GetNextPrimeNumber(kMaxInputInteger);
    if (this->fixed_set_size_ > 1)
    {
        std::uniform_int_distribution<> randomize_a
            (1, this->hash_function_coefficient_p_);
        std::uniform_int_distribution<> randomize_b
            (0, this->hash_function_coefficient_p_); 
        
        this->hash_function_coefficient_a_ = randomize_a(mersenne_twister_);
        this->hash_function_coefficient_b_ = randomize_b(mersenne_twister_);
    }
    else
    {
        this->hash_function_coefficient_a_ = 1;
        this->hash_function_coefficient_b_ = 0;
    }
    
    this->InitializeHashTableRows(numbers);
}

bool FixedSet::Contains(int number) const
{
    int column, row;
    
    column = this->GetHashFromKey(number);
    if (this->fixed_set_size_ == 0 || this->fixed_set_size_ < column)
    {
        return false;
    }
    
    row = this->GetHashFromRowAndKey(fixed_set_[column], number);
    if (fixed_set_[column].table_length == 0 || 
        fixed_set_[column].table_length < row)
    {
        return false;
    }
    return fixed_set_[column].values[row] == number;
}

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