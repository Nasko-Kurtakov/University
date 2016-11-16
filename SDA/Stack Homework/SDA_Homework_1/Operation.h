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
//Operation class used to convert symbols to operations 
//currently works only with + - * /
#pragma once
#include "DynamicArray.h"
class Operation {
private:
	char symbol, operation;
public:
	Operation() {};
	~Operation();
	Operation(const Operation& other);
	Operation& operator= (const Operation& other);
	Operation(char symbol, char operation);

	float Calculate(float, float)const;
	void SetSymbol(char symbol);
	void SetOperation(char operation);
	char GetSymbol() const;
	char GetOperation() const;
};

inline Operation::~Operation()
{
	symbol = '\0', operation = '\0';
}

inline Operation::Operation(const Operation & other)
	:symbol(other.GetSymbol()), operation(other.GetOperation())
{

}

inline Operation & Operation::operator=(const Operation & other)
{
	SetSymbol(other.GetSymbol());
	SetOperation(other.GetOperation());
	return *this;
}

inline Operation::Operation(char symbol, char operation)
	:symbol(symbol),
	operation(operation)
{
}

//calculates expression by given to numbers and the operation
float Operation::Calculate(float firstNumber, float secondNumber)const
{
	if (secondNumber == 0)
	{
		throw std::invalid_argument("Deviding by zero");
	}
	switch (operation)
	{
	case '+':return firstNumber + secondNumber; break;
	case '-':return firstNumber - secondNumber; break;
	case '*':return firstNumber * secondNumber; break;
	case '/':return firstNumber / secondNumber; break;
	}
}

inline void Operation::SetSymbol(char symbol)
{
	this->symbol = symbol;
}

inline void Operation::SetOperation(char operation)
{
	this->operation = operation;
}

inline char Operation::GetSymbol() const
{
	return symbol;
}

inline char Operation::GetOperation() const
{
	return operation;
}