
#include <iostream>
#include "CQueue.h"

int main()
{
	CQueue<int>	queue;

	for (int i = 0; i < 20; ++i)
	{
		queue.push(i);
	}

	while (!queue.empty())
	{
		std::cout << queue.front() << std::endl;
		queue.pop();
	}

	system("cls");

	CQueueArray<int, 300>	queue1;

	for (int i = 0; i < 300; ++i)
	{
		queue1.push(i);
	}

	while (!queue1.empty())
	{
		std::cout << queue1.front() << std::endl;
		queue1.pop();
	}

	system("cls");

	CCircleQueue<int>	CircleQueue;

	for (int i = 0; i < 50; ++i)
	{
		CircleQueue.push(i);
	}

	std::cout << "Pop 30" << std::endl;

	for (int i = 0; i < 30; ++i)
	{
		std::cout << CircleQueue.front() << std::endl;
		CircleQueue.pop();
	}

	for (int i = 0; i < 70; ++i)
	{
		CircleQueue.push(i);
	}

	std::cout << "Pop All" << std::endl;

	while (!CircleQueue.empty())
	{
		std::cout << CircleQueue.front() << std::endl;
		CircleQueue.pop();
	}

	return 0;
}
