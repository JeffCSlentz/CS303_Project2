/*

	Program uses FIFO logic for priority of people in the elevator.
	As it passes each floor it checks if the button on the inside of
	the elevator is pushed. If so, drops off the people who wish to 
	get off at that level. Then checks if the outside button was pushed.
	If there is enough room for the number of people, then they are pushed 
	into the elevator. Continues this loop until the elevator is empty.
	
	tick variable keeps track of how many stops were made
*/

#include <iostream>
#include <queue>
#include <cmath>
#include "Floor.h"
#include <cstdlib>
using namespace std;

const int MAX_NUM_FLOORS = 10;
const int MAX_CAPACITY = 10;

void dropOff(int floorNum, queue<Person>& Elevator);
void pickUp(Floor& floors, queue<Person>& Elevator);
void upOrDown(int& floorNum, queue<Person>& Elevator);

int main() {
	queue<Person> Elevator;
	Floor floors[MAX_NUM_FLOORS];
	int tick = 0;

	for (int i = 0; i < MAX_NUM_FLOORS; i++) // For loop, randomize people throughout the floors.
		floors[i].createFloor(i+1); // i sets floor number

	int floorNum = 0;

	do {

		cout << "Number of people on floor " << (floorNum + 1) << ": " << floors[floorNum].size() << endl;
		cout << "Number of people on Elevator: " << Elevator.size() << endl;

		int tempElevatorSize = Elevator.size(); //keeps the value of how many people were on the elevator before they were dropped off

		dropOff(floorNum, Elevator);

		cout << "Dropped off " << (tempElevatorSize - Elevator.size()) << " people" << endl; 

		tempElevatorSize = Elevator.size(); //Reassign the value

		pickUp(floors[floorNum], Elevator);

		cout << "Picked up " << (Elevator.size() - tempElevatorSize) << " people" << endl;
		
		cout << "Number of people left on floor: " << floors[floorNum].size() << endl;

		if (floorNum == 0)
			floorNum++;
		else if (!Elevator.empty())
			upOrDown(floorNum, Elevator);

		cout << endl;
		
	} while (!Elevator.empty());
	


	cout << tick << endl;



	system("pause");
	return 0;
}

void pickUp(Floor& floors, queue<Person>& Elevator) {
	int numPeeps = floors.size();
	for (int j = 0; j < numPeeps; j++) {
		if (Elevator.size() < MAX_CAPACITY) {
			Elevator.push(floors.front());
			floors.pop();
		}
	}
}

void dropOff(int floorNum, queue<Person>& Elevator) {
	if (!Elevator.empty()) {
		int size = Elevator.size();
		for (int i = 0; i < size; i++) {
			if (Elevator.front().desired_floor == floorNum) {
				Elevator.pop();
			}
			else {
				Elevator.push(Elevator.front());
				Elevator.pop();
			}
		}
	}
}

void upOrDown(int& floorNum, queue<Person>& Elevator) {
	if (Elevator.front().desired_floor > floorNum) //if the persons desired floor is up. Go up
		floorNum++;
	else //if its down. Go down.
		floorNum--;
}