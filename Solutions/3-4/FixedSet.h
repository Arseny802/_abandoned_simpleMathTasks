#ifndef FIXEDSET_H
#define FIXEDSET_H

#include <iostream>  /* console "reading" */
#include <fstream>   /* file reading */
#include <cstring>   /* strncmp() */
#include <sstream>   /* parse string of integers */
#include <stdlib.h>  /* atoi */
#include <algorithm>
#include <vector>
#include <string>
#include <random>

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
