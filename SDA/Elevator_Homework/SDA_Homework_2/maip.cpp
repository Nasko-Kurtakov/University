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
#pragma once
#include "ElevatorLogic.h"
#include "Command.h"
#include "ElevatorCommandsList.h"
#include <iostream>
#include <fstream>

using namespace fmi::sda;

int main(int argc, char** argv)
{
	ElevatorCommandsList<Command*> *elavatorCommandsList = readFromFile<Command*>(argv[1]);
	int currentFloor = 1;
	float currentTime = 0;

	while (!elavatorCommandsList->IsEmpty())
	{
		QueueCalculation(elavatorCommandsList, currentFloor,currentTime);
	}
	elavatorCommandsList->~ElevatorCommandsList();
	return 0;
}