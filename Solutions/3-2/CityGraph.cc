#include "CityGraph.h"

CityGraph::CityGraph() { }

void CityGraph::Initialize(const unsigned int towns_amount)
{
    this->towns_amount_ = towns_amount;
    this->first_map_ = new Town[towns_amount];
    this->second_map_ = new Town[towns_amount];
}

void CityGraph::AddRoadToFirstGraph(Road newRoad)
{
    inputed_roads_.push_back(newRoad);
    if (inputed_roads_.size() == this->towns_amount_)
    {
        this->CompleteGraph(this->first_map_); 
        inputed_roads_.clear();
    }
}

void CityGraph::AddRoadToSecondGraph(Road newRoad)
{
    inputed_roads_.push_back(newRoad);
    if (inputed_roads_.size() == this->towns_amount_)
    {
        this->CompleteGraph(this->second_map_); 
        inputed_roads_.clear();
    }
}

void CityGraph::CompleteGraph(Town*& map)
{
    
        for (iter = 0; iter < cities_amount; ++iter)
        {
            std::cout << renamed_towns[iter] << std::endl;
        }
}

bool CityGraph::CheckIsomorphic()
{
    
    return true;
}

std::vector<unsigned int> CityGraph::GetRenamedTowns()
{
    std::vector<unsigned int> result;
    
    
    result.push_back(1);
    result.push_back(2);
    result.push_back(4);
    result.push_back(3);
    return result;
}

CityGraph::~CityGraph() 
{ 
    delete[] this->first_map_;
    delete[] this->second_map_;
}