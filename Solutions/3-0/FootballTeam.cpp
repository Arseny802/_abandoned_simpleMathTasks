#include "FootballTeam.h"

FootballPlayersTeam::FootballPlayersTeam(const unsigned int summaryEfficiency)
{
	this->summaryEfficiency = summaryEfficiency;
}

std::ostream& operator<< (std::ostream& currentOutputStream, 
							const FootballPlayersTeam& footballTeamPlayers)
{
	currentOutputStream << footballTeamPlayers.summaryEfficiency << std::endl;
	
	for (auto iter = footballTeamPlayers.footballPlayerNumbers.begin(); 
		iter != footballTeamPlayers.footballPlayerNumbers.end(); ++iter)
	{
		currentOutputStream << *iter << ' ';
	}
	currentOutputStream << std::endl;
}

FootballTeam::FootballTeam() { }

bool FootballTeam::VerifyInput()
{
	
	return true;
}

void FootballTeam::ReadFromIO()
{
	R_IO riostream;
	
	this->footballPlayersAmount = riostream.ReadNumber();
	this->footballPlayers = riostream.ReadNumbers(this->footballPlayersAmount);
}

void FootballTeam::ReadFromFile(const std::string fileName)
{
	RFiler filer(fileName);
	
	this->footballPlayersAmount = filer.ReadNumber();
	this->footballPlayers = filer.ReadNumbers(this->footballPlayersAmount);
	
	filer.Close();
}

void FootballTeam::PrintFileResult(const std::string fileName)
{
	RFiler filer(fileName);
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
int FootballTeam::Partition (T arr[], int high, int low)  
{
	T pivot = arr[high];
	signed int minValueIndex = (low - 1);
	
	for (int iter = low; iter < high; ++iter)
	{
		if (arr[iter] < pivot)
		{
			++minValueIndex;
			this->Swap(&arr[minValueIndex], &arr[iter]);
		}
	}  
	++minValueIndex;
	this->Swap(&arr[minValueIndex], &arr[high]);
	return minValueIndex;
} 

template<typename T>
void FootballTeam::QuickSort(T arr[], int high, int low)
{
	int partitioningIndex;
	if (low < high)  
	{
		partitioningIndex = this->Partition(arr, high, low);
		this->QuickSort(arr, partitioningIndex - 1, low);
		this->QuickSort(arr, high, partitioningIndex + 1);
	}
}

FootballPlayersTeam FootballTeam::BuildMostEffectiveSolidaryTeam()
{
	FootballPlayersTeam resultTeam;
	unsigned int leftIndex = 0;
	unsigned int rightIndex = 1;
	unsigned int maximumLeftEfficiency = 0;
	unsigned int maximumRightEfficiency = 0;
	unsigned int* sortedArray;
	std::uint64_t summaryEfficiency, maximumEfficiency;
	
	// Parsing special input
	if (this->footballPlayersAmount == 1)
	{
		resultTeam.summaryEfficiency = this->footballPlayers[0];
		resultTeam.footballPlayerNumbers.push_back(1);
		return resultTeam;
	}
	
	sortedArray = new unsigned int[this->footballPlayersAmount];
	std::copy(this->footballPlayers.begin(), 
		this->footballPlayers.end(), sortedArray);
	this->QuickSort(sortedArray, (int)this->footballPlayersAmount - 1);
	
	summaryEfficiency = maximumEfficiency = sortedArray[leftIndex];
	
	while (rightIndex < this->footballPlayersAmount)
	{
		// moving right index right while the condition is fulfilled
		while (sortedArray[leftIndex] + sortedArray[leftIndex + 1] >= 
				sortedArray[rightIndex] && 
				rightIndex < this->footballPlayersAmount)
		{
			summaryEfficiency += sortedArray[rightIndex];
			++rightIndex;
		} 
		
		// getting the answer
		if (maximumEfficiency < summaryEfficiency)
		{
			maximumEfficiency = summaryEfficiency;
			maximumLeftEfficiency  = sortedArray[leftIndex];
			maximumRightEfficiency = sortedArray[rightIndex - 1];
		}
		
		// moving left index right while the condition isn't fulfilled
		while (sortedArray[leftIndex] + sortedArray[leftIndex + 1] <
				sortedArray[rightIndex] && leftIndex < rightIndex)
		{
			summaryEfficiency -= sortedArray[leftIndex];
			++leftIndex;
		}
	}
	
	resultTeam.summaryEfficiency = maximumEfficiency;
	for (unsigned int iter = 0; iter < this->footballPlayersAmount; ++iter)
	{
		if (this->footballPlayers[iter] >= maximumLeftEfficiency &&
			this->footballPlayers[iter] <= maximumRightEfficiency)
		{
			resultTeam.footballPlayerNumbers.push_back(iter + 1);
		}
	}
	
	delete [] sortedArray;
	return resultTeam;
}

void FootballTeam::ClearData()
{
	this->footballPlayersAmount = 0; // if we use class again
	this->footballPlayers.clear();
}

FootballTeam::~FootballTeam()
{
	this->ClearData();
}

