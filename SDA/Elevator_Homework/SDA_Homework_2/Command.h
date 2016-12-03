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
//commands class is needed to hold the read commands
#pragma once
class Command
{
public:
	Command();
	Command(char* cmdType, char* dir, unsigned int floor, float time);
	Command(Command const &);
	Command& operator= (Command const &);
	~Command();
	unsigned int GetFoor()const;
	float GetTime()const;
private:
	char* cmdType;
	char* dir;
	unsigned int floor;
	float time;

};

Command::Command()
{
	cmdType = NULL;
	dir = NULL;
	floor = 0;
	time = 0;
}

Command::Command(char* cmdType, char* dir, unsigned int floor, float time)
	:cmdType(cmdType), dir(dir), floor(floor), time(time)
{
	//empty for now
}

Command::Command(Command const & otherCommand)
	: cmdType(otherCommand.cmdType), dir(otherCommand.dir), floor(otherCommand.floor), time(otherCommand.time)
{
}

Command & Command::operator=(Command const & otherCommand)
{
	Command(otherCommand.cmdType, otherCommand.dir, otherCommand.floor, otherCommand.time);
	return *this;
}

Command::~Command()
{
	delete cmdType;
	delete dir;
	delete this;
}

unsigned int Command::GetFoor() const
{
	return this->floor;
}

float Command::GetTime() const
{
	return this->time;
}
