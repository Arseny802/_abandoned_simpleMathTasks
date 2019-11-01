#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <string>
#include <cstring>
#include <sstream>
#include <stdlib.h> /* atoi */
#include <algorithm>
#include <ctime> /* test proccess time elapsed */
#include <random>

/*
* Run test or IO stream by default.
* Make this variable 'false' to run tests.
* */
const bool kUseIoByDefault = true;

const std::string kTestFileA = "../resource/test-1.txt";
const std::string kTestFileB = "../resource/test-2.txt";
const std::string kTestFileC = "../resource/test-3.txt";
const std::string kTestFileD = "../resource/test-4.txt";
const std::string kTestFileE = "../resource/test-5.txt";


#ifndef FootballTeam_H
#define FootballTeam_H

struct FootballPlayersTeam
{
public:
    std::uint64_t summary_efficiency;
    std::vector<unsigned int> football_player_numbers;

    explicit FootballPlayersTeam(const unsigned int summary_efficiency = 0);
};

class FootballTeam
{
public:
    FootballTeam();
    ~FootballTeam();

    void ReadFromIO();
    void ReadFromFile(const std::string file_name = "");
    void PrintFileResult(const std::string file_name = "");
    void ClearData();
    FootballPlayersTeam BuildMostEffectiveSolidaryTeam();

private:
    std::vector<unsigned int> football_players_;
    unsigned int football_players_amount_;
    std::mt19937 mersenne_twister_;

    template<typename T>
    void Swap(T* left, T* right);
    template<typename T>
    int Partition(T arr[], int low, int high);
    template<typename T>
    void QuickSort(T arr[], int high, int low = 0);
};

#endif // FootballTeam_H

#ifndef R_IO_H
#define R_IO_H

class ReadIo
{
public:
    ReadIo();
    ~ReadIo();

    unsigned int ReadNumber();
    std::vector<unsigned int> ReadNumbers(unsigned int count);
};

#endif // R_IO_H

#ifndef RFILER_H
#define RFILER_H

const char kDelimeter = ' ';

class RFiler
{
public:
    RFiler();
    explicit RFiler(std::string file_name = "");
    ~RFiler();

    bool Open(std::string file_name = "");
    void Close();
    void Read();
    void PrintLastString();

    bool IsFileOpened();
    unsigned int ReadNumber();
    std::vector<unsigned int> ReadNumbers(unsigned int count);

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

std::vector<unsigned int> RFiler::ReadNumbers(unsigned int count)
{
    std::string line, token;
    std::stringstream string_stream;
    std::vector<unsigned int> result(count);

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

ReadIo::ReadIo() { }

unsigned int ReadIo::ReadNumber()
{
    unsigned int result = 0;
    std::cin >> result;
    return result;
}

std::vector<unsigned int> ReadIo::ReadNumbers(const unsigned int count)
{
    std::vector<unsigned int> result(count);

    for (unsigned int iter = 0; iter < count; ++iter)
    {
        std::cin >> result[iter];
    }
    return result;
}

ReadIo::~ReadIo() { }


FootballPlayersTeam::FootballPlayersTeam(const unsigned int summary_efficiency)
{
    this->summary_efficiency = summary_efficiency;
}

void PrintFootballPlayersTeam(const FootballPlayersTeam& football_players_team)
{
    std::cout << football_players_team.summary_efficiency << std::endl;

    for (auto iter = football_players_team.football_player_numbers.begin();
        iter != football_players_team.football_player_numbers.end(); ++iter)
    {
        std::cout << *iter << ' ';
    }
    std::cout << std::endl;
}

FootballTeam::FootballTeam() 
{
    this->mersenne_twister_ = std::mt19937(time(0));
}

void FootballTeam::ReadFromIO()
{
    ReadIo read_io_stream;

    this->football_players_amount_ = read_io_stream.ReadNumber();
    this->football_players_ = read_io_stream.ReadNumbers(
        this->football_players_amount_);
}

void FootballTeam::ReadFromFile(const std::string file_name)
{
    RFiler filer(file_name);

    this->football_players_amount_ = filer.ReadNumber();
    this->football_players_ = filer.ReadNumbers(this->football_players_amount_);

    filer.Close();
}

void FootballTeam::PrintFileResult(const std::string file_name)
{
    RFiler filer(file_name);
    filer.IncreaseLineNumber(2);
    filer.Read();
    filer.Close();
}

template<typename T>
void FootballTeam::Swap(T* left, T* right)
{
    T tmp = *left;
    *left = *right;
    *right = tmp;
}

template<typename T>
int FootballTeam::Partition(T arr[], int high, int low)
{
    std::uniform_int_distribution<> uniform_int_distribution(low, high); 
    T pivot = uniform_int_distribution(mersenne_twister_);
    this->Swap(&arr[high], &arr[pivot]);
    
    signed int min_value_index = low;

    for (int iter = low; iter < high; ++iter)
    {
        if (arr[iter] < arr[high])
        {
            this->Swap(&arr[min_value_index], &arr[iter]);
            ++min_value_index;
        }
    }
    this->Swap(&arr[min_value_index], &arr[high]);
    return min_value_index;
}

template<typename T>
void FootballTeam::QuickSort(T arr[], int high, int low)
{
    int partitioning_index;
    if (low < high)
    {
        partitioning_index = this->Partition(arr, high, low);
        this->QuickSort(arr, partitioning_index - 1, low);
        this->QuickSort(arr, high, partitioning_index + 1);
    }
}

FootballPlayersTeam FootballTeam::BuildMostEffectiveSolidaryTeam()
{
    FootballPlayersTeam result_team;
    bool flag;
    unsigned int left_index = 0;
    unsigned int right_index = 1;
    unsigned int maximum_left_efficiency = 0;
    unsigned int maximum_right_efficiency = 0;
    std::vector<unsigned int> sorted_array;
    std::uint64_t summary_efficiency, maximum_efficiency;

    // Parsing special input
    if (this->football_players_amount_ == 1)
    {
        result_team.summary_efficiency = this->football_players_[0];
        result_team.football_player_numbers.push_back(1);
        return result_team;
    }

    sorted_array = football_players_;
    this->QuickSort(sorted_array.data(),
        static_cast<int>(this->football_players_amount_) - 1);

    summary_efficiency = maximum_efficiency = sorted_array[left_index];

    while (right_index < this->football_players_amount_)
    {
        // moving right index right while the condition is fulfilled
        while (sorted_array[left_index] + sorted_array[left_index + 1] >=
            sorted_array[right_index])
        {
            summary_efficiency += sorted_array[right_index];
            ++right_index;
            if (right_index >= this->football_players_amount_)
            {
                break;
            }
        }

        // getting the answer
        if (maximum_efficiency < summary_efficiency)
        {
            maximum_efficiency = summary_efficiency;
            maximum_left_efficiency = sorted_array[left_index];
            maximum_right_efficiency = sorted_array[right_index - 1];
        }
        if (right_index >= this->football_players_amount_)
        {
            break;
        }

        // moving left index right while the condition isn't fulfilled
        while (sorted_array[left_index] + sorted_array[left_index + 1] <
            sorted_array[right_index] && left_index < right_index)
        {
            summary_efficiency -= sorted_array[left_index];
            ++left_index;
            if (left_index + 1 >= this->football_players_amount_)
            {
                break;
            }
        }
        if (left_index + 1 >= this->football_players_amount_)
        {
            break;
        }
    }

    result_team.summary_efficiency = maximum_efficiency;
    for (unsigned int iter = 0; iter < this->football_players_amount_; ++iter)
    {
        if (this->football_players_[iter] >= maximum_left_efficiency &&
            this->football_players_[iter] <= maximum_right_efficiency)
        {
            if (this->football_players_[iter] == maximum_left_efficiency)
            {
                flag = true;
                for (unsigned int j = 0; j < 
                    result_team.football_player_numbers.size(); ++j)
                {
                    if (maximum_right_efficiency > this->football_players_[iter]
                         + this->football_players_
                         [result_team.football_player_numbers[j] - 1])
                    {
                        flag = false;
                    }
                }
                if (flag)
                {
                    result_team.football_player_numbers.push_back(iter + 1);
                }
            }
            else
            {
                result_team.football_player_numbers.push_back(iter + 1);
            }
        }
    }

    return result_team;
}

void FootballTeam::ClearData()
{
    this->football_players_amount_ = 0; // if we use class again
    this->football_players_.clear();
}

FootballTeam::~FootballTeam()
{
    this->ClearData();
}

inline void TestFile(std::string file_to_run = kTestFileA)
{
    std::clock_t begin;
    FootballTeam football_team;
    FootballPlayersTeam result;

    football_team.ReadFromFile(file_to_run);
    result = football_team.BuildMostEffectiveSolidaryTeam();

    std::cout << "Testing file '" << file_to_run << "'" << std::endl;
    begin = std::clock();

    std::cout << "Result:   " << std::endl;
    PrintFootballPlayersTeam(result);
    std::cout << "Expected: " << std::endl;
    football_team.PrintFileResult(file_to_run);
    
    football_team.ClearData();
    
    std::cout << "Proccess finished in " << 
        double(std::clock() - begin) / CLOCKS_PER_SEC << 
        " seconds." << std::endl;
    std::cout << "________\n\n";
}

inline void RunTest()
{
    TestFile(kTestFileA);
    TestFile(kTestFileB);
    TestFile(kTestFileC);
    TestFile(kTestFileD);
    TestFile(kTestFileE);
}

int main(int argc, char* argv[])
{
    FootballTeam football_team;
    std::string file_name;
    FootballPlayersTeam result;

    std::ios_base::sync_with_stdio(false);

    if (argc == 1)
    {
        if (kUseIoByDefault)
        {
            football_team.ReadFromIO();
            result = football_team.BuildMostEffectiveSolidaryTeam();
            PrintFootballPlayersTeam(result);
            football_team.ClearData();
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
                football_team.ReadFromFile(kTestFileA);
            }
            else if (strcmp(argv[1], "--io") == 0)
            {
                football_team.ReadFromIO();
            }
            else
            {
                std::cout << "No programm input specified." << std::endl;
                system("pause");
                return 0;
            }

            result = football_team.BuildMostEffectiveSolidaryTeam();
            PrintFootballPlayersTeam(result);
            football_team.ClearData();
        }
    }
    return 0;
}