#ifndef RFILER_H
#define RFILER_H

#include <iostream>  /* console "reading" */
#include <fstream>   /* file reading */
#include <cstring>   /* strncmp() */
#include <sstream>   /* parse string of integers */
#include <stdlib.h>  /* atoi */
#include <ctime>     /* test proccess time elapsed */
#include <algorithm>
#include <vector>
#include <string>
#include <random>

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