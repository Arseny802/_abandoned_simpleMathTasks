#include "Sequence.h"

Sequence::Sequence() { }

bool Sequence::VerifyInput()
{
	// length
	if (this->currentSequenceLength > 1000 || 
		this->currentSequenceLength == 0) return false;
	if (this->currentSequenceLength != this->currentSequence.size()) return false;
	
	// items
	for (unsigned short iter = 0; iter < this->currentSequenceLength; ++iter)
	{
		if (this->currentSequence[iter] > 1000000000 || 
			this->currentSequence[iter] < -1000000000) return false;
	}
	return true;
}

void Sequence::ReadFromIO()
{
	R_IO riostream;
	
	this->currentSequenceLength = riostream.ReadNumber();
	this->currentSequence = riostream.ReadNumbers(this->currentSequenceLength);
}

void Sequence::ReadFromFile(std::string fileName)
{
	RFiler filer(fileName);
	
	this->currentSequenceLength = filer.ReadNumber();
	this->currentSequence = filer.ReadNumbers(this->currentSequenceLength);
	
	filer.Close();
}

void Sequence::PrintFileResult(std::string fileName)
{
	RFiler filer(fileName);
	filer.PrintLastString();
	filer.Close();
}

std::vector<int> Sequence::Calculate()
{
	std::vector<int> result;
	bool moreOne, moreTwo;
	int minIndex, minValue;
	
	result.push_back(this->currentSequence[0]);
	moreOne = this->currentSequence[1] > this->currentSequence[0];
	
	for (unsigned short iter = 2; iter < this->currentSequenceLength; ++iter)
	{
		minIndex = iter - 1;
		moreTwo = this->currentSequence[iter] > this->currentSequence[minIndex];
		if (moreOne)
		{
			if (moreTwo) 
			{
				/* pushing last element */
				if (iter + 1 >= this->currentSequenceLength)
				{
					minValue = this->currentSequence[minIndex];
					while (this->currentSequence[--minIndex] < minValue)
						minValue = this->currentSequence[minIndex];
					result.push_back(this->currentSequence[minIndex + 2]);
				}
				else continue;
			}
			else
			{
				/* searching min value in increasing row*/
				minValue = this->currentSequence[minIndex--];
				while (this->currentSequence[minIndex] > this->currentSequence[iter] && 
					this->currentSequence[minIndex] > result.back())
				{
					minValue = this->currentSequence[minIndex];
					--minIndex;
				}
				result.push_back(minValue);
				moreOne = moreTwo;
				
				/* pushing last element */
				if (iter + 1 >= this->currentSequenceLength)
					result.push_back(this->currentSequence[iter]);
			}
		}
		else
		{
			if (moreTwo)
			{
				result.push_back(this->currentSequence[minIndex]);
				moreOne = moreTwo;
			}
			else continue;
		}
	}
	return result;
}

void Sequence::ClearData()
{
	this->currentSequenceLength = 0;
	this->currentSequence.clear();
}

Sequence::~Sequence()
{
	this->ClearData();
}

