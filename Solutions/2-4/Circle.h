#ifndef CIRCLE_H
#define CIRCLE_H

#include "R_IO.h"
#include "RFiler.h"

#include <vector>
#include <math.h>

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
