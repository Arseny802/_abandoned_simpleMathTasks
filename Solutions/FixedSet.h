#ifndef FIXEDSET_H
#define FIXEDSET_H

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

class FixedSet
{
public:
    FixedSet();
    void Initialize(const std::vector<int>& numbers);
    bool Contains(int number) const;
};

#endif // FIXEDSET_H
