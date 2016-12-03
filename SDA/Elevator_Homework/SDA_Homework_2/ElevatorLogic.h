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
// file that holds the logic of the elevator and helper functions
#pragma once
#include<iostream>
#include "Command.h"
#include "ElevatorCommandsList.h"
namespace fmi {
	namespace sda {
		float absoluteValue(float v)
		{
			return v * ((v > 0) - (v < 0));
		}

		float timeFromFloorToFloor(int fromFloor, int toFloor)
		{
			float timePerFloor = 5.0;
			return absoluteValue(toFloor - fromFloor)*timePerFloor;
		}

		void printFloorData(int currentTime, int currentFloor, int nextFloor, char* direction)
		{
			std::cout << currentTime + timeFromFloorToFloor(currentFloor, nextFloor) << " " << nextFloor << " " << direction << std::endl;
		}

		template<class dataType>
		void removeUntilTime(ElevatorCommandsList<dataType>* elavatorCommandsList, int floor, float time)
		{
			//removes all commands for a single floor
			for (size_t i = 0; i < elavatorCommandsList->GetSize(); i++)
			{
				dataType cmd = elavatorCommandsList->PeekAt(i);
				if (cmd->GetFoor() == floor && cmd->GetTime() <= time)
				{
					elavatorCommandsList->RemoveAtIndex(i);
					--i;
				}
			}
		}

		template<class dataType>
		void findFloorToStop(ElevatorCommandsList<dataType>* elavatorCommandsList, int currentFloor, int currentTime, int nextFloor, char* direction)
		{
			for (size_t j = 0; j < elavatorCommandsList->GetSize(); j++)
			{
				dataType floorToCheck = elavatorCommandsList->PeekAt(j);
				if (floorToCheck->GetFoor() == nextFloor && floorToCheck->GetTime() <= timeFromFloorToFloor(currentFloor, floorToCheck->GetFoor()))
				{
					printFloorData(currentTime, currentFloor, nextFloor, direction);
					elavatorCommandsList->RemoveAtIndex(j);
					--j;//needed so we don't skip a floor
				}
			}

		}

		template<class dataType>
		void goingUp(ElevatorCommandsList<dataType>* elavatorCommandsList, int currentFloor, int currentTime, int floorLooking, int endFloor)
		{
			while (floorLooking <= endFloor)
			{
				findFloorToStop(elavatorCommandsList, currentFloor, currentTime, floorLooking, "up");
				++floorLooking;
			}
		}

		template<class dataType>
		void goingDown(ElevatorCommandsList<dataType>* elavatorCommandsList, int currentFloor, int currentTime, int floorLooking, int endFloor)
		{
			while (floorLooking >= endFloor)
			{
				findFloorToStop(elavatorCommandsList, currentFloor, currentTime, floorLooking, "down");
				--floorLooking;
			}
		}

		template<class dataType>
		void QueueCalculation(ElevatorCommandsList<dataType> *elavatorCommandsList, int & currentFloor, float & currentTime)
		{
			dataType cmd = elavatorCommandsList->PeekFront();
			char* dir;
			if (cmd->GetTime() > currentTime)
				currentTime += cmd->GetTime();

			size_t commingFromFloor = currentFloor;
			size_t goingToFloor = cmd->GetFoor();
			if (currentFloor < goingToFloor)
			{
				goingUp(elavatorCommandsList, currentFloor, currentTime, commingFromFloor + 1, goingToFloor - 1);
				dir = "up";
			}
			else
			{
				goingDown(elavatorCommandsList, currentFloor, currentTime, commingFromFloor - 1, goingToFloor + 1);
				dir = "down";
			}


			currentTime += timeFromFloorToFloor(currentFloor, cmd->GetFoor());
			removeUntilTime(elavatorCommandsList, cmd->GetFoor(), currentTime);
			currentFloor = goingToFloor;
			std::cout << currentTime << " " << cmd->GetFoor() << " " << dir << std::endl;

		}

		template<class dataType>
		ElevatorCommandsList<dataType>* readFromFile(char* fileName)
		{
			ElevatorCommandsList<dataType> *elavatorCommandsList = new ElevatorCommandsList<dataType>();
			std::ifstream fileReader(fileName);
			if (fileReader.is_open())
			{
				unsigned int n, k;
				char cmdType[5];
				char dir[5];
				int floor;
				float time;
				fileReader >> n >> k;
				while (k > 0)
				{
					fileReader >> cmdType;
					if (cmdType[0] == 'c')
					{
						fileReader >> dir >> floor >> time;
					}
					else
					{
						fileReader >> floor >> time;
					}

					Command* cmd = new Command(cmdType, dir, floor, time);//dataType error???
					elavatorCommandsList->PushBack(cmd);
					--k;
				}
				return elavatorCommandsList;
				fileReader.close();
			}
			else
			{
				std::cout << "Problem opening file. Check file name and path.\n";
				throw;
			}
		}
	}
}
