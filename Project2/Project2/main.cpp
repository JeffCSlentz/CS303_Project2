/*

	Program uses FIFO logic for priority of people in the elevator.
	As it passes each floor it checks if the button on the inside of
	the elevator is pushed. If so, drops off the people who wish to 
	get off at that level. Then checks if the outside button was pushed.
	If there is enough room for the number of people and if those people
	are headed in the same direction as the priority queue, then they are 
	pushed into the elevator. Continues this loop until no one has pushed 
	the button on any floor.
	
	time is the counter for the number of floors elevator has passed.
	a report is printed off into a text file called "Elevator Report.txt"
	it's contain within the same file as the source and header files.
	longestWait is used to compute the longest wait of all people who 
	used the elevator.
	Max capacity of elevator and the maximum number of floors are contained
	within the floor header file.
*/

#include <iostream>
#include <fstream>
#include <queue>
#include <cmath>
#include "Floor.h"
using namespace std;

int longestWait = 0;

ofstream report;

void dropOff(int floorNum, queue<Person>& Elevator, int& time);
void pickUp(Floor& floors, queue<Person>& Elevator, int& time);
void leftBehind(Floor& floors,queue<Person>& waiting);
void upOrDown(int& floorNum, queue<Person>& Elevator, int& ElevatorTarget);
void printReport(Person person, ofstream& report);

int main() {
	report.open("Elevator Report.txt");
	queue<Person> Elevator;
	queue<Person> waiting;
	Floor floors[MAX_NUM_FLOORS];
	int ElevatorTarget = 0;
	int time = 1;
	bool buttonPushed = false;

	report << "Floor Entered" << '\t' << "Floor Exited" << '\t' << "Time Picked Up" << '\t' << "Time Dropped Off" << endl;

	for (int i = 0; i < MAX_NUM_FLOORS; i++) // For loop, randomize people throughout the floors.
		floors[i].createFloor(i+1); // i sets floor number

	int floorNum = 0;

	do {

		cout << "Number of people on floor " << (floorNum + 1) << ": " << floors[floorNum].size() << endl;
		cout << "Number of people on Elevator: " << Elevator.size() << endl;

		size_t tempElevatorSize = Elevator.size(); //keeps the value of how many people were on the elevator before they were dropped off

		dropOff(floorNum, Elevator, time); //drop off anyone at the current floor

		cout << "Dropped off " << (tempElevatorSize - Elevator.size()) << " people" << endl; 

		tempElevatorSize = Elevator.size(); //Reassign the value

		pickUp(floors[floorNum], Elevator, time); //pick up anyone at the current floor

		leftBehind(floors[floorNum], waiting); //if anyone is left behind on the floor. Push them into the waiting queue.
	
		cout << "Picked up " << (Elevator.size() - tempElevatorSize) << " people" << endl;
		
		cout << "Number of people left on floor: " << floors[floorNum].size() << endl;

		cout << endl;

		time++; //time increments the number of times the elevator has passed a floor.

		if ((floorNum == 0) && (!Elevator.empty())) {
			buttonPushed = true;
			floorNum++;
		}
		else if (!Elevator.empty()) {
			upOrDown(floorNum, Elevator, ElevatorTarget);
			buttonPushed = true;
		}
		else {
			if (!waiting.empty()) {
				waiting.front().current_floor;
				waiting.pop();
				buttonPushed = true;
			}
			else
				buttonPushed = false;
		}

	} while (buttonPushed);
	
	cout << time << endl;
	
	report << "\nLongest Wait time: " << longestWait << endl;
	report << "Elevator total time: " << time << endl;

	report.close();

	system("pause");
	return 0;
}

void pickUp(Floor& floors, queue<Person>& Elevator, int& time) {
	size_t numPeeps = floors.size();//use size_t (switch it out for int and youll see why)
	for (int j = 0; j < numPeeps; j++) { //go through the number of people on the floor
		if (Elevator.size() < MAX_CAPACITY) { //if the elevator is not full
			if ((Elevator.empty()) || (floors.front().direction == Elevator.front().direction)) {// and the person is going the same direction
				Person temp = floors.front(); //push them into the elevator
				floors.pop();
				temp.time_picked_up = time;
				Elevator.push(temp);
			}
			if (floors.is_empty())
				break;
			floors.push(floors.front()); //go to the next person in line
			floors.pop();
		}
	}
}

void dropOff(int floorNum, queue<Person>& Elevator, int& time) {
	if (!Elevator.empty()) {
		size_t size = Elevator.size();
		for (int i = 0; i < size; i++) {
			if (Elevator.front().desired_floor == floorNum) {
				Person temp = Elevator.front();
				temp.time_dropped_off = time;
				printReport(temp, report); //add the dropped off person to the report text file.
				Elevator.pop();
			}
			else {
				Elevator.push(Elevator.front());
				Elevator.pop();
			}
		}
	}
}

void leftBehind(Floor& floors, queue<Person>& waiting) {
	if (!floors.is_empty()) { //if there is someone left on the floor, push them into the waiting queue.
		for (int i = 0; i < floors.size(); i++) {
			waiting.push(floors.front());
			floors.push(floors.front());
			floors.pop();
		}
	}
}

void upOrDown(int& floorNum, queue<Person>& Elevator, int& ElevatorTarget) {
	if (Elevator.front().desired_floor > floorNum) //if the persons desired floor is up. Go up
		floorNum++;
	else //if its down. Go down.
		floorNum--;
}

void printReport(Person person, ofstream &report) { //Prints into a text file
	report << person.current_floor << '\t' << '\t' << person.desired_floor << '\t' << '\t' << person.time_picked_up 
		   << '\t' << '\t' << person.time_dropped_off << endl;
	if ((person.time_dropped_off - person.time_picked_up) > longestWait)
		longestWait = person.time_dropped_off - person.time_picked_up;
}
