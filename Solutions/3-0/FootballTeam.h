#ifndef FootballTeam_H
#define FootballTeam_H

#include "R_IO.h"
#include "RFiler.h"

#include <vector>
#include <cstdint>
#include <math.h>

struct FootballPlayersTeam
{
public:
	std::uint64_t summaryEfficiency;
	std::vector<unsigned int> footballPlayerNumbers;
	
	FootballPlayersTeam(const unsigned int summaryEfficiency = 0);
};
std::ostream& operator<< (std::ostream& currentOutputStream, 
							const FootballPlayersTeam& footballTeamPlayers);

class FootballTeam
{
public:
	FootballTeam();
	~FootballTeam();
	
	bool VerifyInput();
	void ReadFromIO();
	void ReadFromFile(const std::string fileName = "");
	void PrintFileResult(const std::string fileName = "");
	void ClearData();
	FootballPlayersTeam BuildMostEffectiveSolidaryTeam();
	
private:
	std::vector<unsigned int> footballPlayers;
	unsigned int footballPlayersAmount;
	
template<typename T>
	void Swap(T* left, T* right);
template<typename T>
	int Partition (T arr[], int low, int high);
template<typename T>
	void QuickSort(T arr[], int high, int low = 0);
};

#endif // FootballTeam_H
