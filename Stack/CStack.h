#pragma once

#include <assert.h>

template <typename T>
class CStackNode
{
	template <typename T>
	friend class CStack;

private:
	CStackNode()
	{
		m_pNext = nullptr;
	}

	~CStackNode()
	{
	}

private:
	T		m_Data;
	CStackNode<T>* m_pNext;
};

template <typename T>
class CStack
{
public:
	CStack()
	{
		m_pNode = nullptr;
		m_iSize = 0;
	}

	~CStack()
	{
		clear();
	}

private:
	typedef CStackNode<T>	Node;
	typedef CStackNode<T>* PNode;

private:
	PNode	m_pNode;
	int		m_iSize;

public:
	void push(const T& data)
	{
		PNode	pNode = new Node;

		pNode->m_Data = data;

		if (m_pNode)
			pNode->m_pNext = m_pNode;

		m_pNode = pNode;

		++m_iSize;
	}

	T top()	const
	{
		assert(m_iSize != 0);

		return m_pNode->m_Data;
	}

	void pop()
	{
		assert(m_iSize != 0);

		PNode	pNode = m_pNode->m_pNext;
		delete	m_pNode;

		m_pNode = pNode;

		--m_iSize;
	}

	void clear()
	{
		PNode	pNode = m_pNode;

		while (pNode)
		{
			PNode	pNext = pNode->m_pNext;
			delete	pNode;
			pNode = pNext;
		}

		m_pNode = nullptr;
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

template <typename T>
class CStackArray
{
public:
	CStackArray()
	{
		m_iCapacity = 4;
		m_iSize = 0;
		m_pArray = new T[m_iCapacity];
	}

	~CStackArray()
	{
		delete[]	m_pArray;
	}

private:
	T* m_pArray;
	int	m_iSize;
	int	m_iCapacity;

public:
	void push(const T& data)
	{
		if (m_iSize == m_iCapacity)
		{
			m_iCapacity *= 2;

			T* pArray = new T[m_iCapacity];

			memcpy(pArray, m_pArray, sizeof(T) * m_iSize);

			delete[]	m_pArray;

			m_pArray = pArray;
		}

		m_pArray[m_iSize] = data;
		++m_iSize;
	}

	T top()	const
	{
		assert(m_iSize != 0);

		return m_pArray[m_iSize - 1];
	}

	void pop()
	{
		assert(m_iSize != 0);

		--m_iSize;
	}

	void clear()
	{
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