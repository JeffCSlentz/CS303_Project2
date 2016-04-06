#pragma once
using namespace std;
#include <iostream>
#include "Person.h"
#include <queue>

const int MAX_NUM_FLOORS = 10;
const int MAX_CAPACITY = 20;

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