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
//prefix to postfix algorithm based on http://www.manojagarwal.co.in/conversion-from-prefix-to-postfix/
#pragma once
#include <fstream>
#include <iostream>
#include <iomanip> // for set precision

#include "DynamicArray.h"
#include "Operation.h"
#include "Stack.h"

float findNumber(char numAsChar)
{
	switch (numAsChar)
	{
	case '0':return 0; break;
	case '1':return 1; break;
	case '2':return 2; break;
	case '3':return 3; break;
	case '4':return 4; break;
	case '5':return 5; break;
	case '6':return 6; break;
	case '7':return 7; break;
	case '8':return 8; break;
	case '9':return 9; break;
	}
}

int absoluteValue(int v)
{
	return v * ((v > 0) - (v < 0));
}

float power(float base, int degree)
{
	if (degree == 0) return 1;
	for (int i = 1; i < absoluteValue(degree); i++)
	{
		base *= base;
	}
	if (degree <= 0)
	{
		return 1 / base;
	}
	return base;
}

float convertArrayToNumber(DynamicArray<char>* pArr)
{
	unsigned short degree = 0;
	float number = 0;
	for (int i = pArr->GetUsedSize() - 1; i >= 0; --i)
	{
		if (pArr->GetData(i) == '.' || pArr->GetData(i) == ',')
		{
			if (i == 0)
			{
				throw;
				std::cout << std::endl << "Whrong number input!" << std::endl;
				break;
			}
			number /= power(10, pArr->GetUsedSize() - 1 - i);
			degree = 0;
		}
		else if (pArr->GetData(i) == '-')
		{
			if (i != 0)
			{
				throw;
				std::cout << std::endl << "Whrong number input!" << std::endl;
				break;
			}
			else
			{
				number = 0 - number;
			}
		}
		else
		{
			number += findNumber(pArr->GetData(i)) * power(10, degree++);
		}
	}
	return number;
}

Operation findOperation(DynamicArray<Operation>* dArr, char symbol)
{
	for (size_t i = 0; i < dArr->GetUsedSize(); ++i)
	{
		if (dArr->GetData(i).GetSymbol() == symbol)
			return dArr->GetData(i);
	}
	throw std::exception();
}

bool isDigit(char element) {
	if (element >= '0' && element <= '9')
		return true;
	return false;
}

template<class TYPE>
void showResults(Stack<TYPE> * stack)
{
	while (!stack->IsEmpty())
	{
		DynamicArray<typeid(TYPE).name()> *result = new DynamicArray<typeid(TYPE).name()>();
		stack->Pop(*result);
		result->Print();
		result->~DynamicArray();
	}
}
template<class TYPE, class dataType, class operationsTemplate>
float& CalculatePrefix(Stack<TYPE> * calculationStack, dataType data, DynamicArray<operationsTemplate>* operationsArray)
{
	float firstNumber, secondNumber;
	Operation operation;
	float calculationResult;
	calculationStack->Pop(firstNumber);
	calculationStack->Pop(secondNumber);
	try
	{
		operation = findOperation(operationsArray, data);
	}
	catch (const std::exception& ex)
	{
		std::cout << "Operation definition not found for " << data << std::endl;
		throw std::exception();
	}

	try
	{
		calculationResult = operation.Calculate(firstNumber, secondNumber);
	}
	catch (const std::invalid_argument& e)
	{
		std::cout << std::endl << e.what() << std::endl;
		throw std::exception();
	}
	return calculationResult;
}

template<class TYPE>
DynamicArray<TYPE>* postToPrefix(Stack<DynamicArray<TYPE>*> * postfixStack, TYPE operation)
{
	DynamicArray<TYPE> *opnd1 = new DynamicArray<TYPE>(), *opnd2 = new DynamicArray<TYPE>(), *result = new DynamicArray<TYPE>();
	postfixStack->Pop(opnd1);
	postfixStack->Pop(opnd2);
	result->Transfer(*opnd1);
	result->Add(' ');
	result->Transfer(*opnd2);
	result->Add(' ');
	result->Add(operation);
	opnd1->~DynamicArray(), opnd2->~DynamicArray();
	return result;
}

void prefixToPostfixExpression(DynamicArray<char> *prefix, DynamicArray<Operation>* operationsArray)
{
	Stack<DynamicArray<char>*> *postfixStack = new Stack<DynamicArray<char>*>(prefix->GetUsedSize());
	Stack<float> calculationStack = Stack<float>(prefix->GetUsedSize());
	unsigned int operationCounter = 0, numbersCounter = 0;
	for (int i = prefix->GetUsedSize() - 1; i >= 0; i--)
	{
		if (prefix->GetData(i) == ' ')
			continue;
		if (!isDigit(prefix->GetData(i)))
		{
			if (postfixStack->IsEmpty())
			{
				std::cout << "Error! At index" << i << std::endl;
				break;
			}
			else
			{
				//reverse
				DynamicArray<char> *result = postToPrefix(postfixStack, prefix->GetData(i));
				postfixStack->Push(result);

				//calculations must be done here
				float calculationResult;
				try
				{
					calculationResult = CalculatePrefix(&calculationStack, prefix->GetData(i), operationsArray);
				}
				catch (const std::exception&)
				{
					return;
				}
				calculationStack.Push(calculationResult);
				--i;// we are sure that the next char is always delimiter (' ')
				++operationCounter;
			}
		}
		else
		{
			int len = 1;
			while (prefix->GetData(i - 1) != ' ')
			{
				--i;
				++len;
			}
			DynamicArray<char>* oprnd = new DynamicArray<char>();
			for (size_t j = 0; j < len; j++)
			{
				oprnd->Add(prefix->GetData(i + j));
			}
			calculationStack.Push(convertArrayToNumber(oprnd));
			postfixStack->Push(oprnd);
			--i; // we are sure that the next char is always delimiter (' ')
			++numbersCounter;
		}

	}
	if (operationCounter == numbersCounter - 1)
	{
		//show results
		while (!postfixStack->IsEmpty())
		{
			DynamicArray<char>* result = new DynamicArray<char>();
			postfixStack->Pop(result);
			result->Print();
			result->~DynamicArray();
		}
		float result;
		calculationStack.Pop(result);
		std::cout << std::fixed << std::setprecision(5) << std::endl << result;
		postfixStack->~Stack();
		calculationStack.~Stack();
	}
	else
	{
		std::cout << "Prefix expression is not valid." << std::endl;
	}
}

int main(int argc, char** argv)
{
	DynamicArray<char>* prefix = new DynamicArray<char>();
	char *prefixFileName = "prefix.txt", *operationsFileName = "opr.txt";

	std::ifstream fileReader(prefixFileName);
	if (fileReader.is_open())
	{
		char character;
		unsigned int spaceCounter = 0;
		while (fileReader.get(character))
		{
			if (character == ' ')
				++spaceCounter;
			prefix->Add(character);
		}
		fileReader.close();
	}
	else
	{
		std::cout << "Prefix file not found." << std::endl;
		return 0;
	}

	DynamicArray<Operation>* operationsArray;

	fileReader.open(operationsFileName);
	if (fileReader.is_open())
	{
		operationsArray = new  DynamicArray<Operation>(6);
		char symbol, operation;
		char operationDescription[6];

		while (fileReader.getline(operationDescription, 6))
		{
			if (operationDescription[0] == '\0')
				continue;
			Operation opr = Operation();
			opr.SetSymbol(operationDescription[0]);
			opr.SetOperation(operationDescription[2]);
			operationsArray->Add(opr);
		}
		fileReader.close();
	}
	else
	{
		std::cout << "Operations file not found." << std::endl;
		return 0;
	}
	prefixToPostfixExpression(prefix, operationsArray);
	prefix->~DynamicArray();
	operationsArray->~DynamicArray();
	return 0;
}