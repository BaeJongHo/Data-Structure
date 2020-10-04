
#include <iostream>
#include <time.h>
#include "Sort.h"

bool SortInt(const int& iSrc, const int& iDest)
{
	return iSrc > iDest;
}

int main()
{
	srand((unsigned int)time(0));
	rand();

	int	iArray[30] = {};

	for (int i = 0; i < 30; ++i)
	{
		iArray[i] = rand();
	}

	CSort<int>::QuickSort(iArray, 30, SortInt);
	std::cout << "----------Quick Sort----------" << std::endl;
	for (int i = 0; i < 30; ++i)
	{
		std::cout << iArray[i] << std::endl;
	}

	for (int i = 0; i < 30; ++i)
	{
		iArray[i] = rand();
	}

	CSort<int>::MergeSort(iArray, 30, SortInt);
	std::cout << "----------Merge Sort----------" << std::endl;
	for (int i = 0; i < 30; ++i)
	{
		std::cout << iArray[i] << std::endl;
	}

	for (int i = 0; i < 30; ++i)
	{
		iArray[i] = rand();
	}
	
	CSort<int>::HeapSort(iArray, 30, SortInt);
	std::cout << "----------Heap Sort----------" << std::endl;
	for (int i = 0; i < 30; ++i)
	{
		std::cout << iArray[i] << std::endl;
	}

	return 0;
}