#include "ReaderIo.h"

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