#pragma once
#include <iostream>
#include "Person.h"
#include <queue>
using namespace std;

const int MAX_NUM_FLOORS = 10;
const int MAX_CAPACITY = 10;

class Floor {
private:
	int floor_number;
	queue<Person> peeps;
public:
	Floor() { ; }
	void setFloor(int floorNum) { floor_number = floorNum; }
	void push(Person peep) { peeps.push(peep); }
	int getFloorNum() const { return floor_number; }
	size_t size() const { return peeps.size(); }
	bool is_empty() const { return peeps.empty(); }
	Person front() { return peeps.front(); }
	void pop() { peeps.pop(); }
	void createFloor(int floorNum);
};

void Floor::createFloor(int floorNum) {
	int numPeeps = (rand() % MAX_CAPACITY); //Creates a random number of people on each floor.
	setFloor(floorNum);
	for (int j = 0; j < numPeeps; j++) {
		Person person;
		person.current_floor = floorNum;
		int desiredFloor = ((rand() % (MAX_NUM_FLOORS - 1)) + 1);
		while (desiredFloor == floorNum) //While loop so desired floor isnt the same as current floor
			desiredFloor = ((rand() % 9) + 1);
		person.desired_floor = desiredFloor;
		if (person.desired_floor > person.current_floor)
			person.direction = 'u';
		else
			person.direction = 'd';
		push(person);
	}
}
