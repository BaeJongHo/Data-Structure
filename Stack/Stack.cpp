
#include <iostream>
#include "CStack.h"

int main()
{
	CStack<int>	stack;

	for (int i = 0; i < 10; ++i)
	{
		stack.push(i);
	}

	while (!stack.empty())
	{
		std::cout << stack.top() << std::endl;
		stack.pop();
	}

	system("cls");

	CStackArray<int>	stack1;

	for (int i = 0; i < 10; ++i)
	{
		stack1.push(i);
	}

	while (!stack1.empty())
	{
		std::cout << stack1.top() << std::endl;
		stack1.pop();
	}

	return 0;
}
