
#include <iostream>
#include "CList.h"


int main()
{
	CList<int>	listInt;

	for (int i = 0; i < 10; ++i)
	{
		listInt.push_back(i);
	}

	std::cout << "front : " << listInt.front() << std::endl;
	std::cout << "back : " << listInt.back() << std::endl;

	listInt.pop_back();
	listInt.pop_front();

	CList<int>::iterator	iter = listInt.begin();
	CList<int>::iterator	iterEnd = listInt.end();

	++iter;
	++iter;
	std::cout << "Erase Node : " << *iter << std::endl;
	iter = listInt.erase(iter);

	std::cout << "Erase Next Node : " << *iter << std::endl;

	iter = listInt.begin();

	std::cout << "Count : " << listInt.size() << std::endl;

	listInt.erase(7);

	for (; iter != iterEnd; ++iter)
	{
		std::cout << *iter << std::endl;
	}

	std::cout << "============= reverse =============" << std::endl;

	CList<int>::reverse_iterator	riter = listInt.rbegin();
	CList<int>::reverse_iterator	riterEnd = listInt.rend();

	++riter;
	std::cout << "reverse erase : " << *riter << std::endl;

	riter = listInt.erase(riter);
	std::cout << "reverse erase Next : " << *riter << std::endl;

	riter = listInt.rbegin();

	for (; riter != riterEnd; ++riter)
	{
		std::cout << *riter << std::endl;
	}

	listInt.clear();

	for (int i = 0; i < 10; ++i)
	{
		listInt.push_back(i);
	}

	iter = listInt.begin();
	++iter;

	iterEnd = listInt.end();
	--iterEnd;
	--iterEnd;

	listInt.erase(iter, iterEnd);


	std::cout << "=== 범위삭제 ===" << std::endl;

	iter = listInt.begin();
	iterEnd = listInt.end();

	for (; iter != iterEnd; ++iter)
	{
		std::cout << *iter << std::endl;
	}

	system("cls");

	CList<int>	listInt2;

	listInt2.push_back(10);
	listInt2.push_back(3);
	listInt2.push_back(6);
	listInt2.push_back(2);
	listInt2.push_back(1);
	listInt2.push_back(70);
	listInt2.push_back(40);
	listInt2.push_back(25);
	listInt2.push_back(39);
	listInt2.push_back(15);

	listInt2.Sort(listInt2.begin(), listInt2.end());

	iter = listInt2.begin();
	iterEnd = listInt2.end();

	for (; iter != iterEnd; ++iter)
	{
		std::cout << *iter << std::endl;
	}

	return 0;
}