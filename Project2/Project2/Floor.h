#pragma once
#include <iostream>
#include "Person.h"
#include <queue>
using namespace std;

class Floor {
private:
	int floor_number;
	queue<Person> peeps;
public:
	Floor() { ; }
	void setFloor(int floorNum) { floor_number = floorNum; }
	void push(Person peep) { peeps.push(peep); }
	int getFloorNum() const { return floor_number; }
	int size() const { return peeps.size(); }
	bool is_empty() const { return peeps.empty(); }
	Person front() { return peeps.front(); }
	void pop() { peeps.pop(); }
	void createFloor(int floorNum);
};

void Floor::createFloor(int floorNum) {
	int numPeeps = (rand() % 10); //Creates a random number of people on each floor.
	setFloor(floorNum);
	for (int j = 0; j < numPeeps; j++) {
		Person person;
		person.current_floor = floorNum;
		int desiredFloor = ((rand() % 9) + 1);
		while (desiredFloor == floorNum) //While loop so desired floor isnt the same as current floor
			desiredFloor = ((rand() % 9) + 1);
		person.desired_floor = desiredFloor;
		push(person);
	}
}