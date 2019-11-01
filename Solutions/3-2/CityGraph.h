#ifndef CITYGRAPH_H
#define CITYGRAPH_H

#include <iostream>  /* console "reading" */
#include <fstream>   /* file reading */
#include <cstring>   /* strncmp() */
#include <sstream>   /* parse string of integers */
#include <stdlib.h>  /* atoi */
#include <algorithm>
#include <vector>
#include <string>
#include <random>

struct Town
{
public:
    unsigned int number;
    Town * road_left;
}

class CityGraph
{
public:
    CityGraph();
    void Initialize(const std::vector<int>& numbers);
    bool Contains(int number) const;
    
private:
    Town* graph;
};

#endif // CITYGRAPH_H
