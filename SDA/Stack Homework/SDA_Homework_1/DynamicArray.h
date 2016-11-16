/**
*
* Solution to homework task
* Data Structures Course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Atanas Kurtakov
* @idnumber 61943
* @task 1
* @compiler VS
*
*/
//DynamicArray implementation is based on the samples by Atanas Semerdzhiev
//* URL: https://github.com/semerdzhiev/sdp-samples

#include<iostream>
#pragma once

template<class TYPE>
class DynamicArray
{
private:
	TYPE *pData;

	size_t Size;

	size_t Used;
	void reallocate(size_t);
public:
	DynamicArray();
	~DynamicArray();
	DynamicArray(const DynamicArray& other);
	DynamicArray& operator= (const DynamicArray& other);
	DynamicArray(size_t startingSize);

	void Add(const TYPE& element);
	TYPE GetData(int index);
	void Print();
	void Transfer(const DynamicArray& sourceArr);
	size_t GetSize() const;
	size_t GetUsedSize() const;

	friend std::ostream& operator<<(std::ostream& output, const DynamicArray& DA)
	{
		for (size_t i = 0; i < DA.Used; ++i)
		{
			output << DA.pData[i];
		}
		return output;
	}
};
template<class TYPE>
DynamicArray<TYPE>::DynamicArray() :pData(NULL), Size(0), Used(0)
{
}

template<class TYPE>
DynamicArray<TYPE>::DynamicArray(size_t startingSize)
{
	DynamicArray();
	reallocate(startingSize);
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
inline DynamicArray<TYPE>::DynamicArray(const DynamicArray& other)
	:pData(nullptr), Size(other.GetSize()), Used(other.GetUsedSize())
{
}

template<class TYPE>
inline DynamicArray<TYPE>& DynamicArray<TYPE>::operator= (const DynamicArray& other)
{
	if (this != &other)
	{
		reallocate(other.GetUsedSize());
		Size = other.GetSize();
		for (size_t i = 0; i < Size; ++i)
		{
			pData[i] = other->pData[i];
		}
	}
	return *this;
}

template<class TYPE>
inline void DynamicArray<TYPE>::Add(const TYPE& element)
{
	if (Used >= Size)
	{
		size_t NewSize = (Size == 0 ? 2 : Size * 2);

		reallocate(NewSize);
	}

	pData[Used++] = element;
}

template<class TYPE>
inline TYPE DynamicArray<TYPE>::GetData(int index)
{
	return pData[index];
}

template<class TYPE>
inline void DynamicArray<TYPE>::Print()
{
	for (size_t i = 0; i < Used; i++)
	{
		std::cout << pData[i];
	}
}

template<class TYPE>
void DynamicArray<TYPE>::Transfer(const DynamicArray & sourceArr)
{
	for (size_t i = 0; i < sourceArr.Used; i++)
	{
		Add(sourceArr.pData[i]);
	}
}

template<class TYPE>
inline size_t DynamicArray<TYPE>::GetSize() const
{
	return Size;
}

template<class TYPE>
inline size_t DynamicArray<TYPE>::GetUsedSize() const
{
	return Used;;
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