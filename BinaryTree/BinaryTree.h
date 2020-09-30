#pragma once

#include <assert.h>

template <typename Key, typename Value>
class CBinaryTreeNode
{
	template <typename Key, typename Value>
	friend class CBinaryTree;
	template <typename Key, typename Value>
	friend class CBinaryTreeIterator;

private:
	CBinaryTreeNode()
	{
		m_pLeft = nullptr;
		m_pRight = nullptr;
		m_pParent = nullptr;
		m_pNext = nullptr;
		m_pPrev = nullptr;
	}

	~CBinaryTreeNode()
	{
	}

private:
	CBinaryTreeNode<Key, Value>* m_pLeft;
	CBinaryTreeNode<Key, Value>* m_pRight;
	CBinaryTreeNode<Key, Value>* m_pParent;
	CBinaryTreeNode<Key, Value>* m_pNext;
	CBinaryTreeNode<Key, Value>* m_pPrev;

public:
	Key		first;
	Value	second;
};

template <typename Key, typename Value>
class CBinaryTreeIterator
{
	template <typename Key, typename Value>
	friend class CBinaryTree;

public:
	CBinaryTreeIterator()
	{
		m_pNode = nullptr;
	}

	~CBinaryTreeIterator()
	{
	}

private:
	CBinaryTreeNode<Key, Value>* m_pNode;

public:
	bool operator == (const CBinaryTreeIterator<Key, Value>& iter)	const
	{
		return m_pNode == iter.m_pNode;
	}

	bool operator != (const CBinaryTreeIterator<Key, Value>& iter)	const
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

	CBinaryTreeNode<Key, Value>* operator -> ()	const
	{
		return m_pNode;
	}
};

template <typename Key, typename Value>
class CBinaryTree
{
public:
	CBinaryTree()
	{
		m_pRoot = nullptr;
		m_pBegin = new Node;
		m_pEnd = new Node;

		m_pBegin->m_pNext = m_pEnd;
		m_pEnd->m_pPrev = m_pBegin;

		m_iSize = 0;
	}

	~CBinaryTree()
	{
		clear();
		delete	m_pBegin;
		delete	m_pEnd;
	}

private:
	typedef CBinaryTreeNode<Key, Value>		Node;
	typedef CBinaryTreeNode<Key, Value>* PNode;

public:
	typedef CBinaryTreeIterator<Key, Value>	iterator;

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

			delete	iter.m_pNode;
			iter.m_pNode = pNext;

			--m_iSize;

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

		delete	pDeleteNode;

		--m_iSize;

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
		if (pNode->first >= key)
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
};