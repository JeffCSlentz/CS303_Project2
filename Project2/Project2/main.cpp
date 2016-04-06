/*

	Program uses FIFO logic for priority of people in the elevator.
	As it passes each floor it checks if the button on the inside of
	the elevator is pushed. If so, drops off the people who wish to 
	get off at that level. Then checks if the outside button was pushed.
	If there is enough room for the number of people and if those people
	are headed in the same direction as the priority queue, then they are 
	pushed into the elevator. Continues this loop until no one has pushed 
	the button on any floor.
	
	Time is the counter for the number of floors elevator has passed.
	A report is printed off into a text file called "Elevator Report.txt"
	and stored in the same location as the project file.
	Max capacity of elevator and the maximum number of floors are contained
	within the floor header file "Floor.h".
*/

#include "Elevator.h"

int main() {
	ofstream report;
	report.open("Elevator Report.txt");
	queue<Person> waiting;
	Floor floors[MAX_NUM_FLOORS];
	Elevator Elevator;
	int time = 1;
	bool buttonPushed;

	report << "Floor Entered" << '\t' << "Floor Exited" << '\t' << "Time Picked Up" << '\t' << "Time Dropped Off" << endl;

	for (int i = 0; i < MAX_NUM_FLOORS; i++) // For loop, randomize people throughout the floors.
		floors[i].createFloor(i); // i sets floor number. Floors are ranked from 0 to the Maximum Number of Floors minus 1.

	int floorNum = 0;

	do {
		buttonPushed = false;

		Elevator.dropOff(floorNum, time, report); //drop off anyone at the current floor and print them to the report.

		Elevator.pickUp(floors[floorNum], time); //pick up anyone at the current floor

		if (Elevator.empty()) //if elevator is empty, check if button is pushed
		{
			for (int i = 0; i < MAX_NUM_FLOORS; i++) {
				if (!floors[i].is_empty()) {
					if (floors[i].getFloorNum() > floorNum)
						floorNum++;
					else
						floorNum--;
					buttonPushed = true;
					break;
				}
			}
		}
		else {
			Elevator.upOrDown(floorNum);
			buttonPushed = true;
		}

		time++; //time increments the number of times the elevator passes a floor

	} while (buttonPushed);

	
	report << "\nLongest Wait time: " << Elevator.getLongestWait() << endl;
	report << "Elevator total time: " << time << endl;

	report.close();

	system("pause");
	return 0;
}
