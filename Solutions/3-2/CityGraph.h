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
    Town* roads;
};

struct Road
{
    unsigned int point_a;
    unsigned int point_b;
};

class CityGraph
{
public:
    CityGraph();
    ~CityGraph();
    
    
    void Initialize(const unsigned int towns_amount);
    void AddRoadToFirstGraph(Road newRoad);
    void AddRoadToSecondGraph(Road newRoad);
    
    bool CheckIsomorphic();
    std::vector<unsigned int> GetRenamedTowns();
    
private:
    unsigned int towns_amount_;
    Town* first_map_;
    Town* second_map_;
    std::vector<Road> inputed_roads_;
    
    void CompleteGraph(Town*& map);
};

#endif // CITYGRAPH_H
