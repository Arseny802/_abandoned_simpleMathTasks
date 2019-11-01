#include "RFiler.h"

RFiler::RFiler() { }

RFiler::RFiler(std::string fileName) 
{ 
	this->currentFileName = fileName;
	this->currentFileStream.open(fileName.c_str());
}

bool RFiler::Open(std::string fileName) 
{ 
	this->currentFileName = fileName;
	this->currentFileStream.open(fileName.c_str());
	return this->IsFileOpened();
}

void RFiler::Close() 
{ 
	if (this->IsFileOpened())
		this->currentFileStream.close();
}

void RFiler::Read()
{
	std::string line;
	
	if (this->currentFileStream.is_open()) 
	{
		while (getline(this->currentFileStream, line)) 
		{
			std::cout << line << '\n';
		}
		this->currentFileStream.close();
	} 
	else 
	{
		std::cout << "File for reading \"" 
			<< this->currentFileName << "\" is closed!\n"; 
	}
}

void RFiler::PrintLastString()
{
	std::string line;
	
	if (this->currentFileStream.is_open()) 
	{
		while (getline(this->currentFileStream, line)) 
			continue;
		std::cout << line << '\n';
		this->currentFileStream.close();
	} 
	else 
	{
		std::cout << "File for reading \"" 
			<< this->currentFileName << "\" is closed!\n";
	}
}

bool RFiler::IsFileOpened()
{
	return this->currentFileStream.is_open();
}

unsigned int RFiler::ReadNumber()
{
	std::string line;
	unsigned int result = 0;
	
	if (this->currentFileStream.is_open()) 
	{
		if (getline(this->currentFileStream, line)) 
		{
			result = atoi(line.c_str());
		}
		else 
		{
			std::cout << "Error occurred while file \"" 
				<< this->currentFileName << "\" reading - no lines!\n";
		}
		++this->currentLineNumber;
	} 
	else 
	{
		std::cout << "File for reading \"" 
			<< this->currentFileName << "\" is closed!\n"; 
	}
	
	return result;
}

std::vector<unsigned int> RFiler::ReadNumbers(unsigned int count)
{
	std::string line, token;
	std::stringstream sStream;
	std::vector<unsigned int> result(count);
	
	if (this->currentFileStream.is_open()) 
	{
		if (getline(this->currentFileStream, line)) 
		{
			sStream.str(line);
			for (unsigned int iter = 0; iter < count; ++iter)
			{
				std::getline(sStream, token, delimeter);
				result[iter] = atoi(token.c_str());
			}
		}
		else 
		{
			std::cout << "Error occurred while file \"" 
				<< this->currentFileName << "\" reading - no lines!\n";
		}
		++this->currentLineNumber;
	} 
	else 
	{
		std::cout << "File for reading \"" 
			<< this->currentFileName << "\" is closed!\n";
	}
	
	return result;
}

bool RFiler::SetLineNumber(unsigned int newLineNumber)
{
	if (newLineNumber > this->currentLineNumber)
		return this->IncreaseLineNumber(newLineNumber - this->currentLineNumber);
	else if (newLineNumber < this->currentLineNumber)
		return this->IncreaseLineNumber(this->currentLineNumber - newLineNumber);
	return true;
}

bool RFiler::IncreaseLineNumber(unsigned int numberFor)
{
	std::string line;
	for (unsigned int iter = 0; iter < numberFor; ++iter)
	{
		if (!getline(this->currentFileStream, line)) 
			return false;
		++this->currentLineNumber;
	}
	return true;
}

bool RFiler::DecreaseLineNumber(unsigned int numberFor)
{
	std::string line;
	unsigned int newPosition = currentLineNumber - numberFor;
	
	if (newPosition < 0)
		return false;
	
	this->currentFileStream.seekg (0, this->currentFileStream.beg);
	
	for (unsigned int iter = 0; iter < newPosition; ++iter)
	{
		if (!getline(this->currentFileStream, line)) 
			return false;
		++this->currentLineNumber;
	}
	return true;
}

RFiler::~RFiler() 
{ 
	if (this->IsFileOpened())
		this->currentFileStream.close();
}

