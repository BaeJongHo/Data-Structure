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

		// ���� ��尡 �ִ��� �Ǵ��Ѵ�.
		iterator	iter = find(key, m_pRoot);

		if (iter.m_pNode == m_pEnd)
			return iter;

		// �ڽ��� ���� ����� ��� �׳� �����.
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

		// ���ʿ��� ���� ū ��带 ã�´�.
		if (iter.m_pNode->m_pLeft)
		{
			pDeleteNode = LeftMax(iter.m_pNode->m_pLeft);
			bFindLeft = true;
		}

		else
		{
			pDeleteNode = RightMin(iter.m_pNode->m_pRight);
		}

		// ���� ����� ������ ���� ��带 ��ü�Ѵ�.
		iter.m_pNode->first = pDeleteNode->first;
		iter.m_pNode->second = pDeleteNode->second;

		// ���� ����� ���� Ȥ�� ������ �ڽĳ�尡 ���� ��� ���� ����� �ڸ���
		// ��ü�ϰ� �Ѵ�.
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
		// ���ʿ� ��ġ�� ���
		if (pNode->first >= key)
		{
			// ���� �ڽ� ��尡 ���� ��� ���� �ڽ����� ������ش�.
			if (!pNode->m_pLeft)
			{
				PNode pNewNode = new Node;

				pNewNode->first = key;
				pNewNode->second = value;

				pNode->m_pLeft = pNewNode;
				pNewNode->m_pParent = pNode;

				// �θ����� ������带 ���´�.
				PNode	pPrev = pNode->m_pPrev;

				pPrev->m_pNext = pNewNode;
				pNewNode->m_pPrev = pPrev;

				pNewNode->m_pNext = pNode;
				pNode->m_pPrev = pNewNode;

				return pNewNode;
			}

			// ���� �ڽ� ��尡 ���� ��� ���� �ڽĳ�带 �־��־ �ٽ� Ž���Ѵ�.
			else
			{
				return insert(key, value, pNode->m_pLeft);
			}
		}

		// �����ʿ� ��ġ�� ���
		// ������ �ڽ� ��尡 ���� ��� ������ �ڽ����� ������ش�.
		if (!pNode->m_pRight)
		{
			PNode pNewNode = new Node;

			pNewNode->first = key;
			pNewNode->second = value;

			pNode->m_pRight = pNewNode;
			pNewNode->m_pParent = pNode;

			// �θ����� ������带 ���´�.
			PNode	pNext = pNode->m_pNext;

			pNext->m_pPrev = pNewNode;
			pNewNode->m_pNext = pNext;

			pNewNode->m_pPrev = pNode;
			pNode->m_pNext = pNewNode;

			return pNewNode;
		}

		// ������ �ڽ� ��尡 ���� ��� ������ �ڽĳ�带 �־��־ �ٽ� Ž���Ѵ�.
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

		// key�� �� ���� ��� ������ Ž���Ѵ�.
		if (pNode->first >= key)
			return find(key, pNode->m_pLeft);

		// �������� Ž���Ѵ�.
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