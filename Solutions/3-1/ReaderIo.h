#ifndef READER_IO_H
#define READER_IO_H

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

class ReaderIo
{
public:
    ReaderIo();
    ~ReaderIo();

    unsigned int ReadNumber();
    std::vector<int> ReadNumbers(const unsigned int amount);
};

#endif // READER_IO_H