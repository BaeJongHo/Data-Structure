#pragma once

#include <assert.h>

template <typename Key, typename Value>
class CAVLTreeNode
{
	template <typename Key, typename Value>
	friend class CAVLTree;
	template <typename Key, typename Value>
	friend class CAVLTreeIterator;

private:
	CAVLTreeNode()
	{
		m_pLeft = nullptr;
		m_pRight = nullptr;
		m_pParent = nullptr;
		m_pNext = nullptr;
		m_pPrev = nullptr;
	}

	~CAVLTreeNode()
	{
	}

private:
	CAVLTreeNode<Key, Value>* m_pLeft;
	CAVLTreeNode<Key, Value>* m_pRight;
	CAVLTreeNode<Key, Value>* m_pParent;
	CAVLTreeNode<Key, Value>* m_pNext;
	CAVLTreeNode<Key, Value>* m_pPrev;

public:
	Key		first;
	Value	second;

public:	// 디버깅용 출력함수.
	void Output()
	{
		std::cout << "Key : " << first << " Value : " << second << std::endl;
		std::cout << "Left : ";

		if (!m_pLeft)
			std::cout << "없음" << std::endl;

		else
			std::cout << m_pLeft->first << std::endl;

		std::cout << "Right : ";

		if (!m_pRight)
			std::cout << "없음" << std::endl;

		else
			std::cout << m_pRight->first << std::endl;

		std::cout << "Parent : ";

		if (!m_pParent)
			std::cout << "없음" << std::endl;

		else
			std::cout << m_pParent->first << std::endl;
	}
};

template <typename Key, typename Value>
class CAVLTreeIterator
{
	template <typename Key, typename Value>
	friend class CAVLTree;

public:
	CAVLTreeIterator()
	{
		m_pNode = nullptr;
	}

	~CAVLTreeIterator()
	{
	}

private:
	CAVLTreeNode<Key, Value>* m_pNode;

public:
	bool operator == (const CAVLTreeIterator<Key, Value>& iter)	const
	{
		return m_pNode == iter.m_pNode;
	}

	bool operator != (const CAVLTreeIterator<Key, Value>& iter)	const
	{
		return m_pNode != iter.m_pNode;
	}

	void operator ++ ()
	{
		m_pNode = m_pNode->m_pNext;
	}

	void operator ++ (int)
	{
		m_pNode = m_pNode->m_pNext;
	}

	void operator -- ()
	{
		m_pNode = m_pNode->m_pPrev;
	}

	void operator -- (int)
	{
		m_pNode = m_pNode->m_pPrev;
	}

	CAVLTreeNode<Key, Value>* operator -> ()	const
	{
		return m_pNode;
	}
};

template <typename Key, typename Value>
class CAVLTree
{
public:
	CAVLTree()
	{
		m_pRoot = nullptr;
		m_pBegin = new Node;
		m_pEnd = new Node;

		m_pBegin->m_pNext = m_pEnd;
		m_pEnd->m_pPrev = m_pBegin;

		m_iSize = 0;
	}

	~CAVLTree()
	{
		clear();
		delete	m_pBegin;
		delete	m_pEnd;
	}

private:
	typedef CAVLTreeNode<Key, Value>		Node;
	typedef CAVLTreeNode<Key, Value>* PNode;

public:
	typedef CAVLTreeIterator<Key, Value>	iterator;

private:
	PNode		m_pRoot;
	PNode		m_pBegin;
	PNode		m_pEnd;
	int			m_iSize;

public:
	void insert(const Key& key, const Value& value)
	{
		if (!m_pRoot)
		{
			m_pRoot = new Node;

			m_pRoot->first = key;
			m_pRoot->second = value;

			m_pRoot->m_pNext = m_pEnd;
			m_pEnd->m_pPrev = m_pRoot;

			m_pRoot->m_pPrev = m_pBegin;
			m_pBegin->m_pNext = m_pRoot;
		}

		else
		{
			PNode pNewNode = insert(key, value, m_pRoot);
		}

		++m_iSize;
	}

	int size()	const
	{
		return m_iSize;
	}

	bool empty()	const
	{
		return m_iSize == 0;
	}

	void clear()
	{
		PNode	pNode = m_pBegin->m_pNext;

		while (pNode != m_pEnd)
		{
			PNode	pNext = pNode->m_pNext;
			delete	pNode;
			pNode = pNext;
		}

		m_pBegin->m_pNext = m_pEnd;
		m_pEnd->m_pPrev = m_pBegin;

		m_iSize = 0;

		m_pRoot = nullptr;
	}

	iterator begin()	const
	{
		iterator	iter;
		iter.m_pNode = m_pBegin->m_pNext;
		return iter;
	}

	iterator end()	const
	{
		iterator	iter;
		iter.m_pNode = m_pEnd;
		return iter;
	}

	iterator find(const Key& key)	const
	{
		assert(m_iSize != 0);

		return find(key, m_pRoot);
	}

	iterator erase(const Key& key)
	{
		assert(m_iSize != 0);

		// 지울 노드가 있는지 판단한다.
		iterator	iter = find(key, m_pRoot);

		if (iter.m_pNode == m_pEnd)
			return iter;

		// 자식이 없는 노드일 경우 그냥 지운다.
		if (!iter.m_pNode->m_pLeft && !iter.m_pNode->m_pRight)
		{
			PNode	pNext = iter.m_pNode->m_pNext;
			PNode	pPrev = iter.m_pNode->m_pPrev;

			pPrev->m_pNext = pNext;
			pNext->m_pPrev = pPrev;

			if (!iter.m_pNode->m_pParent)
				m_pRoot = nullptr;

			else
			{
				if (iter.m_pNode->m_pParent->m_pLeft == iter.m_pNode)
					iter.m_pNode->m_pParent->m_pLeft = nullptr;

				else
					iter.m_pNode->m_pParent->m_pRight = nullptr;
			}

			PNode	pParent = iter.m_pNode->m_pParent;

			delete	iter.m_pNode;
			iter.m_pNode = pNext;

			--m_iSize;

			ReBalance(pParent);

			return iter;
		}

		PNode	pDeleteNode = nullptr;
		bool	bFindLeft = false;

		// 왼쪽에서 가장 큰 노드를 찾는다.
		if (iter.m_pNode->m_pLeft)
		{
			pDeleteNode = LeftMax(iter.m_pNode->m_pLeft);
			bFindLeft = true;
		}

		else
		{
			pDeleteNode = RightMin(iter.m_pNode->m_pRight);
		}

		// 지울 노드의 값으로 현재 노드를 대체한다.
		iter.m_pNode->first = pDeleteNode->first;
		iter.m_pNode->second = pDeleteNode->second;

		// 지울 노드의 왼쪽 혹은 오른쪽 자식노드가 있을 경우 지울 노드의 자리를
		// 대체하게 한다.
		if (bFindLeft)
		{
			if (pDeleteNode->m_pParent->m_pLeft == pDeleteNode)
				pDeleteNode->m_pParent->m_pLeft = pDeleteNode->m_pLeft;

			else
				pDeleteNode->m_pParent->m_pRight = pDeleteNode->m_pLeft;

			if (pDeleteNode->m_pLeft)
				pDeleteNode->m_pLeft->m_pParent = pDeleteNode->m_pParent;
		}

		else
		{
			if (pDeleteNode->m_pParent->m_pLeft == pDeleteNode)
				pDeleteNode->m_pParent->m_pLeft = pDeleteNode->m_pRight;

			else
				pDeleteNode->m_pParent->m_pRight = pDeleteNode->m_pRight;

			if (pDeleteNode->m_pRight)
				pDeleteNode->m_pRight->m_pParent = pDeleteNode->m_pParent;
		}

		PNode	pNext = pDeleteNode->m_pNext;
		PNode	pPrev = pDeleteNode->m_pPrev;

		pNext->m_pPrev = pPrev;
		pPrev->m_pNext = pNext;

		if (bFindLeft)
			iter.m_pNode = iter.m_pNode->m_pNext;

		else
			iter.m_pNode = iter.m_pNode;

		PNode	pParent = pDeleteNode->m_pParent;

		delete	pDeleteNode;

		--m_iSize;

		ReBalance(pParent);

		return iter;
	}

private:
	PNode insert(const Key& key, const Value& value, PNode pNode)
	{
		// 왼쪽에 배치할 경우
		if (pNode->first >= key)
		{
			// 왼쪽 자식 노드가 없을 경우 왼쪽 자식으로 만들어준다.
			if (!pNode->m_pLeft)
			{
				PNode pNewNode = new Node;

				pNewNode->first = key;
				pNewNode->second = value;

				pNode->m_pLeft = pNewNode;
				pNewNode->m_pParent = pNode;

				// 부모노드의 이전노드를 얻어온다.
				PNode	pPrev = pNode->m_pPrev;

				pPrev->m_pNext = pNewNode;
				pNewNode->m_pPrev = pPrev;

				pNewNode->m_pNext = pNode;
				pNode->m_pPrev = pNewNode;

				// 노드를 추가했으면 밸런스가 맞추어져 있는지를 판단해야 한다.
				ReBalance(pNewNode);

				return pNewNode;
			}

			// 왼쪽 자식 노드가 있을 경우 왼쪽 자식노드를 넣어주어서 다시 탐색한다.
			else
			{
				return insert(key, value, pNode->m_pLeft);
			}
		}

		// 오른쪽에 배치할 경우
		// 오른쪽 자식 노드가 없을 경우 오른쪽 자식으로 만들어준다.
		if (!pNode->m_pRight)
		{
			PNode pNewNode = new Node;

			pNewNode->first = key;
			pNewNode->second = value;

			pNode->m_pRight = pNewNode;
			pNewNode->m_pParent = pNode;

			// 부모노드의 다음노드를 얻어온다.
			PNode	pNext = pNode->m_pNext;

			pNext->m_pPrev = pNewNode;
			pNewNode->m_pNext = pNext;

			pNewNode->m_pPrev = pNode;
			pNode->m_pNext = pNewNode;

			// 노드를 추가했으면 밸런스가 맞추어져 있는지를 판단해야 한다.
			ReBalance(pNewNode);

			return pNewNode;
		}

		// 오른쪽 자식 노드가 있을 경우 오른쪽 자식노드를 넣어주어서 다시 탐색한다.
		return insert(key, value, pNode->m_pRight);
	}

	iterator find(const Key& key, PNode pNode)	const
	{
		if (!pNode)
			return end();

		else if (pNode->first == key)
		{
			iterator	iter;
			iter.m_pNode = pNode;
			return iter;
		}

		// key가 더 작을 경우 왼쪽을 탐색한다.
		if (pNode->first > key)
			return find(key, pNode->m_pLeft);

		// 오른쪽을 탐색한다.
		return find(key, pNode->m_pRight);
	}

	PNode LeftMax(PNode pNode)
	{
		if (!pNode->m_pRight)
			return pNode;

		return LeftMax(pNode->m_pRight);
	}

	PNode RightMin(PNode pNode)
	{
		if (!pNode->m_pLeft)
			return pNode;

		return RightMin(pNode->m_pLeft);
	}

	PNode RotationLeft(PNode pNode)
	{
		// 부모노드를 얻어온다.
		PNode	pParent = pNode->m_pParent;

		// 기준노드의 오른쪽 자식을 얻어온다.
		PNode	pRight = pNode->m_pRight;

		// 기준노드를 오른쪽 자식노드의 왼쪽 자식으로 붙여준다.
		// 오른쪽 자식노드가 왼쪽자식노드를 가지고 있을 수도 있으므로
		// 미리 자식노드를 얻어둔다.
		PNode	pLeftChild = pRight->m_pLeft;

		pRight->m_pLeft = pNode;

		// 오른쪽 자식노드의 왼쪽 자식노드를 기준노드의 오른쪽 자식노드로
		// 붙여준다.
		pNode->m_pRight = pLeftChild;

		if (pLeftChild)
			pLeftChild->m_pParent = pNode;

		// 오른쪽 자식노드의 부모를 기준노드의 부모로 지정해준다.
		pRight->m_pParent = pParent;

		if (pParent)
		{
			if (pParent->m_pLeft == pNode)
				pParent->m_pLeft = pRight;

			else
				pParent->m_pRight = pRight;
		}

		else
			m_pRoot = pRight;

		// 기준노드의 부모노드를 변경한다.
		pNode->m_pParent = pRight;

		return pRight;
	}

	PNode RotationRight(PNode pNode)
	{
		// 부모노드를 얻어온다.
		PNode	pParent = pNode->m_pParent;

		// 기준노드의 왼쪽 자식을 얻어온다.
		PNode	pLeft = pNode->m_pLeft;

		// 기준노드를 왼쪽 자식노드의 오른쪽 자식으로 붙여준다.
		// 왼쪽 자식노드가 오른쪽 자식노드를 가지고 있을 수도 있으므로
		// 미리 자식노드를 얻어둔다.
		PNode	pRightChild = pLeft->m_pRight;

		pLeft->m_pRight = pNode;

		// 왼쪽 자식노드의 오른쪽 자식노드를 기준노드의 왼쪽 자식노드로
		// 붙여준다.
		pNode->m_pLeft = pRightChild;

		if (pRightChild)
			pRightChild->m_pParent = pNode;

		// 왼쪽 자식노드의 부모를 기준노드의 부모로 지정해준다.
		pLeft->m_pParent = pParent;

		if (pParent)
		{
			if (pParent->m_pLeft == pNode)
				pParent->m_pLeft = pLeft;

			else
				pParent->m_pRight = pLeft;
		}

		else
			m_pRoot = pLeft;

		// 기준노드의 부모노드를 변경한다.
		pNode->m_pParent = pLeft;

		return pLeft;
	}

	int GetTreeHeight(PNode pNode)
	{
		if (!pNode)
			return 0;

		int	iLeft = GetTreeHeight(pNode->m_pLeft);
		int	iRight = GetTreeHeight(pNode->m_pRight);

		int	iFactor = iLeft > iRight ? iLeft : iRight;

		return iFactor + 1;
	}

	int BalanceFactor(PNode pNode)
	{
		// 왼쪽 서브트리 - 오른쪽 서브트리
		return GetTreeHeight(pNode->m_pLeft) - GetTreeHeight(pNode->m_pRight);
	}

	void ReBalance(PNode pNode)
	{
		if (!pNode)
			return;

		int	iFactor = BalanceFactor(pNode);

		// 오른쪽으로 균형이 무너졌을 경우
		if (iFactor <= -2)
		{
			// 오른쪽 오른쪽으로 균형이 무너졌는지
			// 오른쪽 왼쪽으로 균형이 무너졌는지 판단하기 위해 오른쪽 자식노드를
			// 넣고 값을 다시 구해본다.
			int	iRightFactor = BalanceFactor(pNode->m_pRight);

			// -1이 나올 경우 오른쪽 오른쪽으로 균형이 무너졌을 경우이다.
			if (iRightFactor < 0)
			{
				pNode = RotationLeft(pNode);
			}

			// 오른쪽 왼쪽으로 균형이 무너졌을 경우이다.
			else
			{
				// 오른쪽 자식노드를 중심으로 우회전한다.
				RotationRight(pNode->m_pRight);
				// 기준노드를 중심으로 좌회전한다.
				pNode = RotationLeft(pNode);
			}
		}

		// 왼쪽으로 균형이 무너졌을 경우
		else if (iFactor >= 2)
		{
			int	iLeftFactor = BalanceFactor(pNode->m_pLeft);

			// 왼쪽 왼쪽으로 균형이 무너졌을 경우
			if (iLeftFactor > 0)
			{
				pNode = RotationRight(pNode);
			}

			// 왼쪽 오른쪽으로 균형이 무너졌을 경우
			else
			{
				RotationLeft(pNode->m_pLeft);
				pNode = RotationRight(pNode);
			}
		}

		// 부모노드로 타고들어가며 균형이 무너졌는지를 판단한다.
		ReBalance(pNode->m_pParent);
	}
};

