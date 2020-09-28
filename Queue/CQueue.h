#pragma once

#include <assert.h>

template <typename T>
class CQueueNode
{
	template <typename T>
	friend class CQueue;

private:
	CQueueNode()
	{
		m_pNext = nullptr;
	}

	~CQueueNode()
	{
	}

private:
	T		m_Data;
	CQueueNode<T>* m_pNext;
};

template <typename T>
class CQueue
{
public:
	CQueue()
	{
		m_pHead = nullptr;
		m_pTail = nullptr;
		m_iSize = 0;
	}

	~CQueue()
	{
		clear();
	}

private:
	typedef CQueueNode<T>	Node;
	typedef CQueueNode<T>* PNode;

private:
	PNode	m_pHead;
	PNode	m_pTail;
	int		m_iSize;

public:
	void push(const T& data)
	{
		PNode	pNode = new Node;

		pNode->m_Data = data;

		if (m_iSize == 0)
			m_pHead = pNode;

		else
			m_pTail->m_pNext = pNode;

		m_pTail = pNode;
		++m_iSize;
	}

	T front()	const
	{
		assert(m_iSize != 0);

		return m_pHead->m_Data;
	}

	void pop()
	{
		assert(m_iSize != 0);

		PNode	pNext = m_pHead->m_pNext;

		delete	m_pHead;

		m_pHead = pNext;

		--m_iSize;

		if (m_iSize == 0)
			m_pTail = nullptr;
	}

	void clear()
	{
		PNode	pNode = m_pHead;

		while (pNode)
		{
			PNode	pNext = pNode->m_pNext;
			delete	pNode;
			pNode = pNext;
		}

		m_iSize = 0;
	}

	int size()	const
	{
		return m_iSize;
	}

	bool empty()	const
	{
		return m_iSize == 0;
	}
};

template <typename T, int SIZE = 100>
class CQueueArray
{
public:
	CQueueArray()
	{
		m_iTail = 0;
		m_iHead = 0;
	}

	~CQueueArray()
	{
	}

private:
	T		m_Array[SIZE];
	int		m_iTail;
	int		m_iHead;

public:
	void push(const T& data)
	{
		assert(m_iTail != SIZE);

		m_Array[m_iTail] = data;
		++m_iTail;
	}

	T front()	const
	{
		assert((m_iTail - m_iHead) != 0);

		return m_Array[m_iHead];
	}

	void pop()
	{
		assert((m_iTail - m_iHead) != 0);

		++m_iHead;
	}

	void clear()
	{
		m_iHead = 0;
		m_iTail = 0;
	}

	int size()	const
	{
		return m_iTail - m_iHead;
	}

	bool full()	const
	{
		return m_iTail == SIZE;
	}

	bool empty()	const
	{
		return m_iHead == m_iTail;
	}
};

template <typename T, int SIZE = 100>
class CCircleQueue
{
public:
	CCircleQueue()
	{
		m_iHead = 0;
		m_iTail = 0;
		m_iSize = 0;

		m_iCapacity = SIZE + 1;
	}

	~CCircleQueue()
	{
	}

private:
	T		m_Array[SIZE + 1];
	int		m_iHead;
	int		m_iTail;
	int		m_iCapacity;
	int		m_iSize;

public:
	void push(const T& data)
	{
		assert(m_iSize != SIZE);

		int	iTail = (m_iTail + 1) % m_iCapacity;

		m_Array[iTail] = data;
		m_iTail = iTail;

		++m_iSize;
	}

	T front()	const
	{
		assert(m_iSize != 0);

		int	iHead = (m_iHead + 1) % m_iCapacity;

		return m_Array[iHead];
	}

	void pop()
	{
		assert(m_iSize != 0);

		m_iHead = (m_iHead + 1) % m_iCapacity;
		--m_iSize;
	}

	void clear()
	{
		m_iHead = 0;
		m_iTail = 0;
		m_iSize = 0;
	}

	int size()	const
	{
		return m_iSize;
	}

	bool full()	const
	{
		return m_iSize == SIZE;
	}

	bool empty()	const
	{
		return m_iSize == 0;
	}
};
