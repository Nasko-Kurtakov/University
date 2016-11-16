#include "DynamicArray.h"

template<class TYPE>
DynamicArray<TYPE>::DynamicArray() :pData(nullptr), Size(0), Used(0)
{
}

template<class TYPE>
DynamicArray<TYPE>::~DynamicArray()
{
	delete[] pData;
	pData = nullptr;
	Size = 0;
	Used = 0;
}

template<class TYPE>
void DynamicArray<TYPE>::add(TYPE element)
{
	if (Used >= > Size)
	{
		size_t NewSize = (Size == 0 ? 2 : Size * 2);

		reallocate(NewSize);
	}

	pData[Used++] = Element;
}

template<class TYPE>
TYPE DynamicArray<TYPE>::getData(int index)
{
	return pData[index];
}

template<class TYPE>
void DynamicArray<TYPE>::print()
{
	for (size_t i = 0; i < pda->Used; i++)
	{
		std::cout << pda->pData[i];
	}
}

template<class TYPE>
void DynamicArray<TYPE>::transfer(DynamicArray * sourceArr)
{
	for (size_t i = 0; i < sourceArr->Used; i++)
	{
		add(sourceArr->pData[i]);
	}
}

template<class TYPE>
void DynamicArray<TYPE>::reallocate(size_t newSize)
{
	TYPE* pTemp = new TYPE[newSize];
	size_t min = Size < newSize ? Size : newSize;
	for (size_t i = 0; i < min; i++)
		pTemp[i] = pData[i];

	delete[] pData;

	pData = pTemp;
	Size = newSize;
}