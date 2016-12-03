/**
*
* Solution to homework task
* Data Structures Course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Atanas Kurtakov
* @idnumber 61943
* @task 2
* @compiler VS
*
*/
//Double Linked list implementation is based on the samples by Atanas Semerdzhiev
//* URL: https://github.com/semerdzhiev/sdp-samples

//implementation of priority queue using double linked list
#pragma once
#include <assert.h>
#include "Box.h"
template<class dataType>
class ElevatorCommandsList
{
private:
	Box<dataType> *pFront, *pBack;
	size_t size;
	void Init();
	void CreateQueue(ElevatorCommandsList const & otherQ);
	void DeleteElements();
	void CreateChain(Box<dataType> *pFront);
	Box<dataType>* FindAtIndex(int index) const;
public:
	ElevatorCommandsList();
	ElevatorCommandsList(ElevatorCommandsList const &);
	ElevatorCommandsList& operator= (ElevatorCommandsList const &);
	~ElevatorCommandsList();

	bool PushBack(dataType const &);
	bool PushFront(dataType const &);

	dataType & PeekBack()const;
	dataType & PeekFront()const;
	dataType & PeekAt(int index)const;
	size_t GetSize()const;

	void RemoveAtIndex(int index);
	void RemoveFront();
	void RemoveBack();
	void RemoveAll();

	bool IsEmpty() const;
	bool IsExisting(dataType);
};

template<class dataType>
inline void ElevatorCommandsList<dataType>::Init()
{
	pFront = nullptr;
	pBack = nullptr;
	size = 0;
}

template<class dataType>
void ElevatorCommandsList<dataType>::CreateQueue(ElevatorCommandsList const & otherQ)
{
	Init();
	if (!otherQ.IsEmpty())
	{
		CreateChain(otherQ.pFront);
	}
	this->size = otherQ.GetSize();
}

template<class dataType>
void ElevatorCommandsList<dataType>::DeleteElements()
{
	Box<dataType> *pCurrent = pFront;
	Box<dataType> *pOld = pFront;
	while (pCurrent)
	{
		pOld = pCurrent;
		pCurrent = pCurrent->pNext;
		delete pOld;
	}
}

template<class dataType>
void ElevatorCommandsList<dataType>::CreateChain(Box<dataType>* pFront)
{
	if (pFront)
	{
		// Pointer to the start of the new chain
		Box<dataType>* pNewChain = new Box<dataType>(pFront->data, NULL, pFront->pPrevious);
		this->pFront = pNewChain;
		// Pointer to the element that we have to copy next
		Box<dataType>* pReadFrom = pFront->pPrevious;

		while (pReadFrom)
		{
			pNewChain->pPrevious = pReadFrom;
			pNewChain->pPrevious->pNext = pNewChain;
			this->pBack = pNewChain;
			pNewChain = pReadFrom;
			pReadFrom = pReadFrom->pPrevious;
		}
	}
}

template<class dataType>
inline ElevatorCommandsList<dataType>::ElevatorCommandsList()
{
	Init();
}

template<class dataType>
ElevatorCommandsList<dataType>::ElevatorCommandsList(ElevatorCommandsList const & otherQ)
{
	CreateQueue(otherQ);
}

template<class dataType>
ElevatorCommandsList<dataType>& ElevatorCommandsList<dataType>::operator=(ElevatorCommandsList const &)
{
	if (this != &otherPQ)
	{
		RemoveAll();
		CreateQueue(otherPQ);
	}
	return *this;
}

template<class dataType>
ElevatorCommandsList<dataType>::~ElevatorCommandsList()
{
	if (!this->IsEmpty())
	{
		DeleteElements();
	}
}

template<class dataType>
bool ElevatorCommandsList<dataType>::PushBack(const dataType &  value)
{
	Box<dataType> *pNewBox = new Box<dataType>(value, pBack, NULL);
	if (pNewBox)
	{
		if (IsEmpty())
		{
			pFront = pNewBox;
			pBack = pNewBox;
			pNewBox->pNext = NULL;
			pNewBox->pPrevious = NULL;
		}
		else
		{
			pBack->pPrevious = pNewBox;
			pBack = pNewBox;
		}
		++size;
	}

	return pNewBox != NULL;
}

template<class dataType>
bool ElevatorCommandsList<dataType>::PushFront(dataType const & value)
{
	Box<dataType> *pNewBox = new Box<dataType>(value, NULL, pFront);
	if (pNewBox)
	{
		if (IsEmpty())
		{
			pFront = pNewBox;
			pBack = pNewBox;
			pNewBox->pNext = NULL;
			pNewBox->pPrevious = NULL;
		}
		else
		{
			pFront->pNext = pNewBox;
			pFront = pNewBox;
		}
		++size;
	}
	return pNewBox != NULL;
}

template<class dataType>
dataType & ElevatorCommandsList<dataType>::PeekBack() const
{
	if (!IsEmpty())
	{
		return pBack->data;
	}
}

template<class dataType>
dataType & ElevatorCommandsList<dataType>::PeekFront() const
{
	if (!this->IsEmpty())
	{
		return pFront->data;
	}
}

template<class dataType>
dataType & ElevatorCommandsList<dataType>::PeekAt(int index) const
{
	Box<dataType> *pFound = this->FindAtIndex(index);
	return pFound->data;
}

template<class dataType>
inline size_t ElevatorCommandsList<dataType>::GetSize() const
{
	return this->size;
}

template<class dataType>
Box<dataType>* ElevatorCommandsList<dataType>::FindAtIndex(int index) const
{
	if (index < 0 || index >= this->size)
	{
		return NULL;
	}
	else
	{
		Box<dataType> *p = this->pFront;

		for (int i = 0; i < index; i++)
		{
			p = p->pPrevious;
		}

		return p;
	}
}

template<class dataType>
void ElevatorCommandsList<dataType>::RemoveAtIndex(int index)
{
	if (index == 0)
	{
		this->RemoveFront();
	}
	else if (index == this->size - 1)
	{
		this->RemoveBack();
	}
	else
	{
		assert(this->GetSize() >= 2);

		Box<dataType> *pBoxAtIndex = this->FindAtIndex(index);

		if (index == this->size - 1)
		{
			this->pBack = pBoxAtIndex->pNext;
		}
		if (index == 0)
		{
			this->pFront = pBoxAtIndex->pPrevious;
		}

		pBoxAtIndex->pPrevious->pNext = pBoxAtIndex->pNext;
		pBoxAtIndex->pNext->pPrevious = pBoxAtIndex->pPrevious;

		delete pBoxAtIndex;

		--this->size;
	}
}

template<class dataType>
void ElevatorCommandsList<dataType>::RemoveFront()
{
	if (!this->IsEmpty())
	{
		assert(this->pFront != NULL);

		Box<dataType> *pOldFront = this->pFront;
		this->pFront = this->pFront->pPrevious;

		if (this->pFront == NULL)
		{
			this->pBack = NULL;
		}
		--this->size;
		delete pOldFront;
	}
}

template<class dataType>
void ElevatorCommandsList<dataType>::RemoveBack()
{
	assert(this->pBack != NULL);
	Box<dataType> *pOldBack = this->pBack;
	this->pBack = this->pBack->pNext;

	if (this->pBack == NULL)
	{
		this->pFront == NULL;
	}
	--this->size;
	delete pOldBack;

}

template<class dataType>
void ElevatorCommandsList<dataType>::RemoveAll()
{
	DeleteElements();
	Init();
}

template<class dataType>
bool ElevatorCommandsList<dataType>::IsEmpty() const
{
	if (size == 0)
		return true;
	return false;
}

template<class dataType>
bool ElevatorCommandsList<dataType>::IsExisting(dataType data)
{
	Box<dataType> *p = this->pBack;
	for (size_t i = 0; i < this->size; ++i)
	{
		if (p->data->GetFoor() == data->GetFoor())
			return true;
		p = p->pNext;
	}
	return false;
}