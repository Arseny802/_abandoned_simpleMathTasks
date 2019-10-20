#include "Circle.h"

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

