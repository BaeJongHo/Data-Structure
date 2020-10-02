#include <iostream>
#include "AVLTree.h"

int main()
{
	CAVLTree<int, int>	avlTree;

	for (int i = 0; i < 20; ++i)
	{
		avlTree.insert(i + 1, i + 1);
	}

	CAVLTree<int, int>::iterator	iter = avlTree.begin();
	CAVLTree<int, int>::iterator	iterEnd = avlTree.end();

	for (; iter != iterEnd; ++iter)
	{
		iter->Output();
	}

	avlTree.erase(12);
	avlTree.erase(8);

	system("cls");

	iter = avlTree.begin();
	iterEnd = avlTree.end();

	for (; iter != iterEnd; ++iter)
	{
		iter->Output();
	}

	return 0;
}