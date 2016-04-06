#pragma once
#include "Floor.h"
#include <fstream>

class Elevator {
private:
	char direction;
	queue<Person> people;
	int longestWait = 0;

public:
	size_t size() const { return people.size(); }
	bool empty() const { return people.empty(); }
	void dropOff(int floorNum, int time, ofstream &report);
	void pickUp(Floor& floors, int time);
	void upOrDown(int& floorNum);
	void printReport(Person person, ofstream &report);
	int getLongestWait() const { return longestWait; }
};