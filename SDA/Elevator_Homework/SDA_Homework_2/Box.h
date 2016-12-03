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
#pragma once
#include <assert.h>
//implementation of a structure which will hold the the two pointers and the data
template<class dataType>
class Box {
public:
	dataType data;
	Box<dataType> *pNext, *pPrevious;
public:
	Box(dataType const & data, Box<dataType> *pNext, Box<dataType> *pPrevious);
	bool HasNext() const;
	bool HasPrevious() const;
};

template<class dataType>
Box<dataType>::Box(dataType const & data, Box<dataType>* pNext = NULL, Box<dataType>* pPrevious = NULL)
	:data(data), pNext(pNext), pPrevious(pPrevious)
{
}

template<class dataType>
bool Box<dataType>::HasNext() const
{
	return this->pNext != NULL;
}

template<class dataType>
bool Box<dataType>::HasPrevious() const
{
	return this->pPrevious != NULL;
}
