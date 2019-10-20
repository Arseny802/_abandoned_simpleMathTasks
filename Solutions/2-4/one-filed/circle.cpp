#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <stdlib.h> /* atoi */
#include <math.h>

/* 
 * Run test or IO stream by default.
 * Comment next line to run tests.
 * */
#define DEFAULT_IO
/* 
 * Enable this to run silent.
 * Program will not pause in the end.
 * */
#define SILENT_MOD

#define TEST_FILE_1 "../resource/test-1.txt"
#define TEST_FILE_2 "../resource/test-2.txt"
#define TEST_FILE_3 "../resource/test-3.txt"
#define TEST_FILE_4 "../resource/test-4.txt"

#define DELIMETER ' '

#ifndef RFILER_H
#define RFILER_H

class RFiler
{
public:
	RFiler();
	RFiler(std::string fileName = "");
	~RFiler();
	
	bool Open(std::string fileName = "");
	void Close();
	void Read();
	void PrintLastString();
	
	bool IsFileOpened();
	int ReadNumber();
	std::vector<int> ReadNumbers(unsigned int count);
	
	bool SetLineNumber(unsigned int newLineNumber);
	bool IncreaseLineNumber(unsigned int numberFor = 1);
	bool DecreaseLineNumber(unsigned int numberFor = 1);
private:
	std::ifstream currentFileStream;
	std::string currentFileName;
	unsigned int currentLineNumber;
};

#endif // RFILER_H

#ifndef R_IO_H
#define R_IO_H

class R_IO
{
public:
	R_IO();
	~R_IO();
	
	int ReadNumber();
	std::vector<int> ReadNumbers(unsigned int count);
};

#endif // R_IO_H

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
	else std::cout << "File for reading \"" << this->currentFileName << "\" is closed!\n"; 
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
	else std::cout << "File for reading \"" << this->currentFileName << "\" is closed!\n"; 
}

bool RFiler::IsFileOpened()
{
	return this->currentFileStream.is_open();
}

int RFiler::ReadNumber()
{
	std::string line;
	int result = 0;
	
	if (this->currentFileStream.is_open()) 
	{
		if (getline(this->currentFileStream, line)) 
		{
			result = atoi(line.c_str());
		}
		else std::cout << "Error occurred while file \"" << this->currentFileName << "\" reading - no lines!\n";
		++this->currentLineNumber;
	} 
	else std::cout << "File for reading \"" << this->currentFileName << "\" is closed!\n"; 
	
	return result;
}

std::vector<int> RFiler::ReadNumbers(unsigned int count)
{
	std::string line, token;
	std::stringstream sStream;
	std::vector<int> result(count);
	
	if (this->currentFileStream.is_open()) 
	{
		if (getline(this->currentFileStream, line)) 
		{
			sStream.str(line);
			for (unsigned int iter = 0; iter < count; ++iter)
			{
				std::getline(sStream, token, DELIMETER);
				result[iter] = atoi(token.c_str());
			}
		}
		else std::cout << "Error occurred while file \"" << this->currentFileName << "\" reading - no lines!\n";
		++this->currentLineNumber;
	} 
	else std::cout << "File for reading \"" << this->currentFileName << "\" is closed!\n";
	
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

R_IO::R_IO()
{
}

int R_IO::ReadNumber()
{
	int result = 0;
	std::cin >> result;
	return result;
}

std::vector<int> R_IO::ReadNumbers(unsigned int count)
{
	std::string line, token;
	std::stringstream sStream;
	std::vector<int> result(count);
	for (unsigned int iter = 0; iter < count; ++iter)
		std::cin >> result[iter];
	
	return result;
}

R_IO::~R_IO()
{
}

#ifndef CIRCLE_H
#define CIRCLE_H

struct Point
{
	short x;
	short y;
	double radius;
	
	Point(short x = 0, short y = 0);
	static double GetRadius(double x = 0, double y = 0);
};

class Circle
{
public:
	Circle();
	~Circle();
	
	bool VerifyInput();
	void ReadFromIO();
	void ReadFromFile(std::string fileName = "");
	void PrintFileResult(std::string fileName = "");
	void ClearData();
	double Calculate();
	
private:
	std::vector<Point> pointes;
	unsigned short pointesAmount;
	unsigned short minimumPointesAmount;
	
template<typename T>
	void Swap(T* left, T* right);
template<typename T, typename C>
	C Partition (T arr[], C low, C high);
template<typename T, typename C>
	void QuickSort(T arr[], C high, C low = 0);
};

#endif // CIRCLE_H

Point::Point(short x, short y)
{
	this->x = x;
	this->y = y;
	this->radius = this->GetRadius(x, y);
}

double Point::GetRadius(double x, double y)
{
	return sqrt(pow(x, 2) + pow(y, 2));
}

Circle::Circle() { }

bool Circle::VerifyInput()
{
	if (this->pointesAmount > 10000) return false;
	if (this->minimumPointesAmount > this->pointesAmount) return false;
	if (this->minimumPointesAmount < 1) return false;
	
	for (unsigned short iterator = 0; iterator < this->pointesAmount; ++iterator)
	{
		if (this->pointes[iterator].x > 1000) return false;
		if (this->pointes[iterator].x < -1000) return false;
		if (this->pointes[iterator].y > 1000) return false;
		if (this->pointes[iterator].y < -1000) return false;
	}
	return true;
}

void Circle::ReadFromIO()
{
	std::vector<int> tmp;
	R_IO riostream;
	
	tmp = riostream.ReadNumbers(2);
	this->pointesAmount = tmp[0];
	this->minimumPointesAmount = tmp[1];
	this->pointes.resize(this->pointesAmount);
	
	for (unsigned short iter = 0; iter < this->pointesAmount; ++iter)
	{
		tmp = riostream.ReadNumbers(2);
		this->pointes[iter] = Point(tmp[0], tmp[1]);
	}
}

void Circle::ReadFromFile(std::string fileName)
{
	std::vector<int> tmp;
	RFiler filer(fileName);
	
	tmp = filer.ReadNumbers(2);
	this->pointesAmount = tmp[0];
	this->minimumPointesAmount = tmp[1];
	this->pointes.resize(this->pointesAmount);
	
	for (unsigned short iter = 0; iter < this->pointesAmount; ++iter)
	{
		tmp = filer.ReadNumbers(2);
		this->pointes[iter] = Point(tmp[0], tmp[1]);
	}
	
	filer.Close();
}

void Circle::PrintFileResult(std::string fileName)
{
	RFiler filer(fileName);
	filer.PrintLastString();
	filer.Close();
}

template<typename T>
void Circle::Swap(T* left, T* right)
{
	T tmp = *left;
	*left = *right;
	*right = tmp;
}

template<typename T, typename C>
C Circle::Partition (T arr[], C high, C low)  
{
	T pivot = arr[high];
	C minValueIndex = (low - 1);
	
	for (unsigned short iter = low; iter <= high - 1; ++iter)
	{
		if (arr[iter] < pivot)
			this->Swap(&arr[++minValueIndex], &arr[iter]);
	}  
	this->Swap(&arr[minValueIndex + 1], &arr[high]);
	return (minValueIndex + 1);
} 

template<typename T, typename C>
void Circle::QuickSort(T arr[], C high, C low)
{
	C partitioningIndex;
	if (low < high)  
	{
		partitioningIndex = this->Partition(arr, high, low); 
		this->QuickSort(arr, partitioningIndex - 1, low);
		this->QuickSort(arr, high, partitioningIndex + 1);
	}
}

double Circle::Calculate()
{
	double radiusArray[this->pointesAmount];
	double maxRadius = 0;
	double left = 0;
	double right = 0;
	double xPoint = 0;
	unsigned short leftPointCoefficient = 0;
	unsigned short rightPointCoefficient = 0;
	unsigned short searchPointIndex = 0;
	unsigned char foundPointes = 0;
	
	for (unsigned short iterator = 0; iterator < this->pointesAmount; ++iterator)
		radiusArray[iterator] = this->pointes[iterator].radius;
	this->QuickSort(radiusArray,  this->pointesAmount - 1, 0);
	maxRadius = radiusArray[this->minimumPointesAmount - 1];
	
	for (unsigned short firstIterator = 0; firstIterator < this->pointesAmount; ++firstIterator)
	{
		if (maxRadius < Point::GetRadius(this->pointes[firstIterator].x, this->pointes[firstIterator].y)) continue;
		
		left  = this->pointes[firstIterator].x - sqrt(pow(maxRadius, 2) - pow(this->pointes[firstIterator].y, 2));
		right = this->pointes[firstIterator].x + sqrt(pow(maxRadius, 2) - pow(this->pointes[firstIterator].y, 2));
		
		leftPointCoefficient = 1;
		rightPointCoefficient = 1;
		
		for (unsigned short secondIterator = 0; secondIterator < this->pointesAmount; ++secondIterator)
		{
			if (firstIterator == secondIterator) 
				continue;
			
			if (Point::GetRadius(this->pointes[secondIterator].x + left, 
				this->pointes[secondIterator].y) <= maxRadius) ++leftPointCoefficient;
			
			if (Point::GetRadius(this->pointes[secondIterator].x + right, 
				this->pointes[secondIterator].y) <= maxRadius) ++rightPointCoefficient;
		}
		if (left != right && leftPointCoefficient >= this->minimumPointesAmount) 
		{
			xPoint += left;
			searchPointIndex = firstIterator;
			++foundPointes;
		}
		if (rightPointCoefficient >= this->minimumPointesAmount) 
		{
			xPoint += right;
			searchPointIndex = firstIterator;
			if (left == right) foundPointes = 2;
			else ++foundPointes;
		}
		if (foundPointes >= 2) break;
	}
	
	return Point::GetRadius(this->pointes[searchPointIndex].x + (xPoint / 2), this->pointes[searchPointIndex].y);
}

void Circle::ClearData()
{
	this->pointesAmount = 0;
	this->minimumPointesAmount = 0;
	this->pointes.clear();
}

Circle::~Circle()
{
	this->ClearData();
}

inline void TestFile(std::string fileToRun = TEST_FILE_1)
{
	Circle circle;
	double result;
	
	circle.ReadFromFile(fileToRun);
	if (circle.VerifyInput())
	{
		result = circle.Calculate();
		
		std::cout << "Testing file '" << fileToRun << "'" << std::endl;
		std::cout << "Verifing data in file... ";
		std::cout << (circle.VerifyInput() ? "Ok" : "Error") << std::endl;
		
		std::cout << "Result:   " << std::fixed << result << std::endl;
		std::cout << "Expected: "; 
		circle.PrintFileResult(fileToRun);
		std::cout << "________\n\n"; 
	}
	circle.ClearData();
}

inline void RunTest()
{
	TestFile(TEST_FILE_1);
	TestFile(TEST_FILE_2);
	TestFile(TEST_FILE_3);
	TestFile(TEST_FILE_4);
}

int main(int argc, char* argv[]) 
{
	Circle circle;
	std::string fileName = "";
	
	if (argc == 1) 
	{
#ifdef DEFAULT_IO
		circle.ReadFromIO();
		if (circle.VerifyInput())
			std::cout << circle.Calculate() << std::endl;
		circle.ClearData();
#else
		RunTest();
#endif
	}
	else 
	{
		if (strcmp(argv[1], "--test") == 0) RunTest();
		else
		{
			if (strcmp(argv[1], "--file") == 0) 
			{
				if (argc == 3) fileName = argv[2];
				circle.ReadFromFile(TEST_FILE_1);
			}
			else if (strcmp(argv[1], "--io") == 0) circle.ReadFromIO();
			else
			{
				std::cout << "No programm input specified." << std::endl;
				system("pause");
				return 0;
			}
			
			if (circle.VerifyInput())
				std::cout << circle.Calculate() << std::endl;
			circle.ClearData();
		}
	}
#ifndef SILENT_MOD
	std::cout << "Programm finished." << std::endl;
	system("pause");
#endif
	return 0;
}