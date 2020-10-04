#pragma once

template <typename T>
class CSort
{
public:
	static void QuickSort(T* pArray, int iCount, bool(*pFunc)(const T&, const T&))
	{
		QuickSort(pArray, 0, iCount - 1, pFunc);
	}

private:
	static int Partition(T* pArray, int iLeft, int iRight, bool(*pFunc)(const T&, const T&))
	{
		int	iLow = iLeft;
		int	iHigh = iRight + 1;

		int	iPivot = pArray[iLeft];

		do
		{
			do
			{
				++iLow;
			} while (iLow <= iRight && pFunc(iPivot, pArray[iLow]));

			do
			{
				--iHigh;
			} while (iHigh >= iLeft && pFunc(pArray[iHigh], iPivot));

			if (iLow < iHigh)
			{
				T	temp = pArray[iLow];
				pArray[iLow] = pArray[iHigh];
				pArray[iHigh] = temp;
			}
		} while (iLow < iHigh);

		T	temp = pArray[iLeft];
		pArray[iLeft] = pArray[iHigh];
		pArray[iHigh] = temp;

		return iHigh;
	}

	static void QuickSort(T* pArray, int iLeft, int iRight, bool(*pFunc)(const T&, const T&))
	{
		if (iLeft < iRight)
		{
			int	iIndex = Partition(pArray, iLeft, iRight, pFunc);

			QuickSort(pArray, iLeft, iIndex - 1, pFunc);
			QuickSort(pArray, iIndex + 1, iRight, pFunc);
		}
	}

public:
	static void MergeSort(T* pArray, int iCount, bool(*pFunc)(const T&, const T&))
	{
		T* pSortArray = new T[iCount];
		MergeSort(pArray, 0, iCount - 1, pSortArray, pFunc);
		delete[]	pSortArray;
	}

private:
	static void MergeSort(T* pArray, int iLeft, int iRight, T* pSortArray, bool(*pFunc)(const T&, const T&))
	{
		if (iLeft < iRight)
		{
			int	iMid = (iLeft + iRight) / 2;
			MergeSort(pArray, iLeft, iMid, pSortArray, pFunc);
			MergeSort(pArray, iMid + 1, iRight, pSortArray, pFunc);
			Merge(pArray, iLeft, iMid, iRight, pSortArray, pFunc);
		}
	}

	static void Merge(T* pArray, int iLeft, int iMid, int iRight, T* pSortArray, bool(*pFunc)(const T&, const T&))
	{
		int	iLeftIdx = iLeft;
		int	iMidIdx = iMid + 1;
		int	iInsertIdx = iLeft;

		while (iLeftIdx <= iMid && iMidIdx <= iRight)
		{
			if (pFunc(pArray[iMidIdx], pArray[iLeftIdx]))
				pSortArray[iInsertIdx++] = pArray[iLeftIdx++];

			else
				pSortArray[iInsertIdx++] = pArray[iMidIdx++];
		}

		// 남아있는 값을 일괄적으로 복사해준다.
		if (iLeftIdx > iMid)
		{
			for (int i = iMidIdx; i <= iRight; ++i)
			{
				pSortArray[iInsertIdx++] = pArray[i];
			}
		}

		else
		{
			for (int i = iLeftIdx; i <= iMid; ++i)
			{
				pSortArray[iInsertIdx++] = pArray[i];
			}
		}

		for (int i = iLeft; i <= iRight; ++i)
		{
			pArray[i] = pSortArray[i];
		}
	}

public:
	static void HeapSort(T* pArray, int iCount, bool(*pFunc)(const T&, const T&))
	{
		T* pHeap = new T[iCount];
		int	iHeapSize = 0;

		for (int i = 0; i < iCount; ++i)
		{
			Insert(pHeap, pArray[i], iHeapSize, pFunc);
			++iHeapSize;
		}

		for (int i = 0; i < iCount; ++i)
		{
			//pop하면서 최소 값부터 배열에 넣어줘서 정렬한다.
			pArray[i] = Pop(pHeap, iHeapSize, pFunc);
			--iHeapSize;
		}

		delete[]	pHeap;
	}

private:
	static void Insert(T* pHeap, const T& data, int iSize, bool(*pFunc)(const T&, const T&))
	{
		pHeap[iSize] = data;

		int	iIndex = iSize;
		int iParent = (iSize - 1) / 2;

		while (iParent >= 0 && data < pHeap[iParent])
		{
			pHeap[iIndex] = pHeap[iParent];
			iIndex = iParent;

			if (iIndex == 0)
				break;

			iParent = (iIndex - 1) / 2;
		}

		pHeap[iIndex] = data;
	}

	static int Pop(T* pHeap, int iSize, bool(*pFunc)(const T&, const T&))
	{
		int result = pHeap[0];
		pHeap[0] = pHeap[iSize - 1];

		int iParent = 0;
		int iLeft = (iParent * 2) + 1;
		int iRight = (iParent * 2) + 2;

		while (1)
		{
			if (iRight < iSize && iLeft < iSize && pFunc(pHeap[iLeft], pHeap[iRight]) && pFunc(pHeap[iParent], pHeap[iRight]))
			{
				int temp = pHeap[iParent];
				pHeap[iParent] = pHeap[iRight];
				pHeap[iRight] = temp;

				iParent = iRight;
			}

			else if (iRight < iSize && iLeft < iSize && pFunc(pHeap[iRight], pHeap[iLeft]) && pFunc(pHeap[iParent], pHeap[iLeft]))
			{
				int temp = pHeap[iParent];
				pHeap[iParent] = pHeap[iLeft];
				pHeap[iLeft] = temp;

				iParent = iLeft;
			}

			else if (iRight < iSize && iLeft >= iSize && pFunc(pHeap[iParent], pHeap[iRight]))
			{
				int temp = pHeap[iParent];
				pHeap[iParent] = pHeap[iRight];
				pHeap[iRight] = temp;

				iParent = iRight;
			}

			else if (iLeft < iSize && iRight >= iSize && pFunc(pHeap[iParent], pHeap[iLeft]))
			{
				int temp = pHeap[iParent];
				pHeap[iParent] = pHeap[iLeft];
				pHeap[iLeft] = temp;

				iParent = iLeft;
			}

			else
				break;

			iLeft = (iParent * 2) + 1;
			iRight = (iParent * 2) + 2;

			if (iLeft >= iSize && iRight >= iSize)
				break;
		}

		return result;
	}
};
