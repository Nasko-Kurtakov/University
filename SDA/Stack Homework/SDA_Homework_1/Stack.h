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
//Stack implementation is based on the samples by Atanas Semerdzhiev
//* URL: https://github.com/semerdzhiev/sdp-samples

#pragma once

#include <assert.h>
template <class TYPE>
class Stack {
public:
	Stack(size_t Size);
	~Stack();
	Stack(Stack const & Other);
	Stack& operator=(Stack const & Other);

	void Push(const TYPE & Element);
	bool Pop(TYPE& Element);

	size_t GetSize() const;
	size_t GetMaxSize() const;
	bool IsEmpty() const;

private:
	void Init();
	void Destroy();
	void CopyFrom(Stack const & Other);

	TYPE* pData;
	size_t Allocated;
	size_t Used;
};

template <class TYPE>
Stack<TYPE>::Stack(size_t Size)
{
	Init();
	pData = new TYPE[Size];
	Allocated = Size;
}

template <class TYPE>
Stack<TYPE>::Stack(Stack const & Other)
{
	Init();
	CopyFrom(Other);
}

template <class TYPE>
Stack<TYPE>::~Stack()
{
	Destroy();
}

template <class TYPE>
Stack<TYPE>& Stack<TYPE>::operator=(Stack<TYPE> const & Other)
{
	if (this != &Other)
	{
		Destroy();
		CopyFrom(Other);
	}

	return *this;
}

//init stack with default parameters
template <class TYPE>
void Stack<TYPE>::Init()
{
	pData = NULL;
	Allocated = 0;
	Used = 0;
}

//
template <class TYPE>
void Stack<TYPE>::Destroy()
{
	delete[] pData;
	Init();
}

template <class TYPE>
void Stack<TYPE>::CopyFrom(Stack<TYPE> const& Other)
{
	if (Other.IsEmpty())
		return;

	pData = new TYPE[Other.Allocated];
	Allocated = Other.Allocated;
	Used = Other.Used;

	for (size_t i = 0; i < Used; i++)
		pData[i] = Other.pData[i];
}

//Add element
template <class TYPE>
void Stack<TYPE>::Push(const TYPE & Element)
{
	assert(Used < Allocated);

	pData[Used++] = Element;
}

//Must note that element is returned when poped instead of taken with Top() and then poped
template<class TYPE>
bool Stack<TYPE>::Pop(TYPE & Element)
{
	if (Used > 0)
	{
		Element = pData[--Used];
		return true;
	}
	return false;
}

//returns current used size
template<class TYPE>
size_t Stack<TYPE>::GetSize() const
{
	return Used;
}

//checks max size as the stack is with fixed size
template<class TYPE>
size_t Stack<TYPE>::GetMaxSize() const
{
	return Allocated;
}

//checks if the stack is empty or not
template<class TYPE>
bool Stack<TYPE>::IsEmpty() const
{
	return Used == 0;
}