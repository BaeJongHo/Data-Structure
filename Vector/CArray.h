#pragma once

#include <assert.h>

template <typename T>
class CArrayNode
{
	template <typename T>
	friend class CArray;
	template <typename T>
	friend class CArrayIterator;

private:
	CArrayNode()
	{
		m_pNext = nullptr;
		m_pPrev = nullptr;
	}

	~CArrayNode()
	{
	}

private:
	T		m_Data;
	CArrayNode<T>* m_pNext;
	CArrayNode<T>* m_pPrev;
};

template <typename T>
class CArrayIterator
{
	template <typename T>
	friend class CArray;

public:
	CArrayIterator()
	{
		m_pNode = nullptr;
	}

	~CArrayIterator()
	{
	}

private:
	CArrayNode<T>* m_pNode;
	CArrayNode<T>* m_pBegin;
	CArrayNode<T>* m_pEnd;

public:
	bool operator == (const CArrayIterator<T>& iter)	const
	{
		return m_pNode == iter.m_pNode;
	}

	bool operator != (const CArrayIterator<T>& iter)	const
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

	CArrayIterator<T> operator + (int iSize)
	{
		CArrayIterator<T>	iter;
		iter.m_pNode = m_pNode;
		iter.m_pBegin = m_pBegin;
		iter.m_pEnd = m_pEnd;

		CArrayNode<T>* pLast = m_pEnd->m_pPrev;

		assert(!(pLast + 2 <= m_pNode + iSize));

		if (pLast + 1 == m_pNode + iSize)
			iter.m_pNode = m_pEnd;

		else
			iter.m_pNode += iSize;

		return iter;
	}

	CArrayIterator<T> operator - (int iSize)
	{
		CArrayIterator<T>	iter;
		iter.m_pNode = m_pNode;
		iter.m_pBegin = m_pBegin;
		iter.m_pEnd = m_pEnd;

		CArrayNode<T>* pFirst = m_pBegin->m_pNext;

		assert(!(pFirst - 2 >= m_pNode - iSize));

		if (pFirst - 1 == m_pNode - iSize)
			iter.m_pNode = m_pBegin;

		else
			iter.m_pNode -= iSize;

		return iter;
	}

	void operator += (int iSize)
	{
		CArrayNode<T>* pLast = m_pEnd->m_pPrev;

		assert(!(pLast + 2 <= m_pNode + iSize));

		if (pLast + 1 == m_pNode + iSize)
			m_pNode = m_pEnd;

		else
			m_pNode += iSize;
	}

	void operator -= (int iSize)
	{
		CArrayNode<T>* pFirst = m_pBegin->m_pNext;

		assert(!(pFirst - 2 >= m_pNode - iSize));

		if (pFirst - 1 == m_pNode - iSize)
			m_pNode = m_pBegin;

		else
			m_pNode -= iSize;
	}

	T& operator * ()	const
	{
		return m_pNode->m_Data;
	}
};

template <typename T>
class CArray
{
public:
	CArray()
	{
		m_iSize = 0;
		m_iCapacity = 4;

		m_pArray = new Node[m_iCapacity];

		m_pBegin = new Node;
		m_pEnd = new Node;

		m_pBegin->m_pNext = m_pEnd;
		m_pEnd->m_pPrev = m_pBegin;
	}

	~CArray()
	{
		delete[]	m_pArray;
		delete	m_pBegin;
		delete	m_pEnd;
	}

private:
	typedef CArrayNode<T>	Node;
	typedef CArrayNode<T>* PNode;

public:
	typedef CArrayIterator<T>	iterator;

private:
	PNode		m_pArray;
	PNode		m_pBegin;
	PNode		m_pEnd;
	int			m_iSize;		// 실제 추가된 개수
	int			m_iCapacity;	// 할당된 전체 배열의 개수

public:
	void resize(int iCapacity)
	{
		m_iCapacity = iCapacity;

		PNode	pArray = new Node[m_iCapacity];

		// 기존 배열에 있던 내용들을 새로 할당한 배열로 옮겨준다.
		memcpy(pArray, m_pArray, sizeof(Node) * m_iSize);

		delete[]	m_pArray;

		m_pArray = pArray;

		m_pBegin->m_pNext = m_pArray;
		m_pArray->m_pPrev = m_pBegin;

		for (int i = 0; i < m_iSize - 1; ++i)
		{
			m_pArray[i].m_pNext = &m_pArray[i + 1];
			m_pArray[i + 1].m_pPrev = &m_pArray[i];
		}

		m_pArray[m_iSize - 1].m_pNext = m_pEnd;
		m_pEnd->m_pPrev = &m_pArray[m_iSize - 1];
	}

	void push_back(const T& data)
	{
		// 배열의 공간이 꽉 찼을 경우 공간을 늘려준다.
		if (m_iSize == m_iCapacity)
			resize(m_iCapacity * 2);

		m_pArray[m_iSize].m_Data = data;

		PNode	pPrev = m_pEnd->m_pPrev;

		pPrev->m_pNext = &m_pArray[m_iSize];
		m_pArray[m_iSize].m_pPrev = pPrev;

		m_pArray[m_iSize].m_pNext = m_pEnd;
		m_pEnd->m_pPrev = &m_pArray[m_iSize];

		++m_iSize;
	}

	void pop_back()
	{
		if (empty())
		{
			assert(false);
		}

		PNode	pPrev = m_pArray[m_iSize - 1].m_pPrev;

		--m_iSize;

		pPrev->m_pNext = m_pEnd;
		m_pEnd->m_pPrev = pPrev;
	}

	int size()	const
	{
		return m_iSize;
	}

	int capacity()	const
	{
		return m_iCapacity;
	}

	bool empty()	const
	{
		return m_iSize == 0;
	}

	void clear()
	{
		m_iSize = 0;

		m_pBegin->m_pNext = m_pEnd;
		m_pEnd->m_pPrev = m_pBegin;
	}

	T& operator [] (int idx)
	{
		assert(!(idx < 0 || idx >= m_iSize));

		return m_pArray[idx].m_Data;
	}

	iterator begin()	const
	{
		iterator	iter;
		iter.m_pBegin = m_pBegin;
		iter.m_pEnd = m_pEnd;
		iter.m_pNode = m_pBegin->m_pNext;
		return iter;
	}

	iterator end()	const
	{
		iterator	iter;
		iter.m_pBegin = m_pBegin;
		iter.m_pEnd = m_pEnd;
		iter.m_pNode = m_pEnd;
		return iter;
	}

	iterator erase(const iterator& iter)
	{
		if (iter.m_pNode == m_pEnd)
			return end();

		int	iIndex = ((int)iter.m_pNode - (int)m_pArray) / sizeof(Node);

		// 뒤의 데이터를 앞으로 가져온다.
		for (int i = iIndex; i < m_iSize - 1; ++i)
		{
			m_pArray[i].m_Data = m_pArray[i + 1].m_Data;
		}

		--m_iSize;

		m_pArray[m_iSize - 1].m_pNext = m_pEnd;
		m_pEnd->m_pPrev = &m_pArray[m_iSize - 1];

		return iter;
	}

	iterator erase(const iterator& first, const iterator& second)
	{
		iterator	iterStart = first;
		iterator	iterEnd = second;

		if (iterStart.m_pNode == m_pBegin)
			iterStart.m_pNode = m_pBegin->m_pNext;

		if (iterEnd.m_pNode == m_pEnd)
			--iterEnd;

		PNode	pPrev = iterStart.m_pNode->m_pPrev;
		PNode	pNext = iterEnd.m_pNode;

		int	iStartIndex = ((int)iterStart.m_pNode - (int)m_pArray) / sizeof(Node);
		int	iEndIndex = ((int)iterEnd.m_pNode - (int)m_pArray) / sizeof(Node);

		// 뒤의 데이터를 앞으로 가져온다.
		int	iCount = m_iSize - iEndIndex - 1;
		for (int i = 0; i < iCount; ++i)
		{
			m_pArray[i + iStartIndex].m_Data = m_pArray[iEndIndex + i + 1].m_Data;
		}

		int	iDeleteCount = iEndIndex - iStartIndex + 1;

		m_iSize -= iDeleteCount;

		m_pArray[m_iSize - 1].m_pNext = m_pEnd;
		m_pEnd->m_pPrev = &m_pArray[m_iSize - 1];

		iterator	iter;
		iter.m_pBegin = m_pBegin;
		iter.m_pEnd = m_pEnd;
		iter.m_pNode = m_pArray + (m_iSize - 1);

		return iter;
	}

	void Sort(const iterator& first, const iterator& second)
	{
		iterator iterStart = first;
		iterator iterEnd = second;

		if (iterEnd == end())
			--iterEnd;

		int iStartIndex = ((int)iterStart.m_pNode - (int)m_pArray) / sizeof(Node);
		int iEndIndex = ((int)iterEnd.m_pNode - (int)m_pArray) / sizeof(Node);

		for (int i = iStartIndex; i <= iEndIndex; ++i)
		{
			for (int j = iStartIndex; j <= iEndIndex - i - 1; ++j)
			{
				if (m_pArray[j].m_Data > m_pArray[j + 1].m_Data)
				{
					int temp = m_pArray[j].m_Data;
					m_pArray[j].m_Data = m_pArray[j + 1].m_Data;
					m_pArray[j + 1].m_Data = temp;
				}
			}
		}
	}
};