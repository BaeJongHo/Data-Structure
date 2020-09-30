
#include <iostream>
#include "BinaryTree.h"

int main()
{
	CBinaryTree<int, const char*>	tree;

	int	iArr[8] = { 50, 40, 80, 30, 15, 25, 10, 100 };

	tree.insert(30, "전사");
	tree.insert(15, "궁수");
	tree.insert(10, "마법사");
	tree.insert(25, "도적");
	tree.insert(50, "해적");
	tree.insert(40, "캐논 슈터");
	tree.insert(80, "메카닉");
	tree.insert(100, "아델");

	CBinaryTree<int, const char*>::iterator	iter = tree.begin();
	CBinaryTree<int, const char*>::iterator	iterEnd = tree.end();

	for (; iter != iterEnd; ++iter)
	{
		std::cout << "Key : " << iter->first <<
			" Value : " << iter->second << std::endl;
	}

	iter = tree.find(200);

	if (iter == tree.end())
		std::cout << "찾는 대상이 없습니다." << std::endl;

	iter = tree.find(10);

	std::cout << "Find Key : " << iter->first <<
		" Value : " << iter->second << std::endl;

	for (int i = 0; i < 8; ++i)
	{
		std::cout << "Delete : " << iArr[i] << std::endl;
		iter = tree.erase(iArr[i]);

		if (iter != tree.end())
			std::cout << "Next : " << iter->first << std::endl;
	}

	iter = tree.begin();
	iterEnd = tree.end();

	for (; iter != iterEnd; ++iter)
	{
		std::cout << "Key : " << iter->first <<
			" Value : " << iter->second << std::endl;
	}

	return 0;
}