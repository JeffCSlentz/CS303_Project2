#include "Elevator.h"

void Elevator::dropOff(int floorNum, int time, ofstream& report) {
	if (!people.empty()) {
		size_t size = people.size();
		for (int i = 0; i < size; i++) {
			if (people.front().desired_floor == floorNum) {
				Person temp = people.front();
				temp.time_dropped_off = time;
				printReport(temp, report); //add the dropped off person to the report text file.
				people.pop();
			}
			else {
				people.push(people.front());
				people.pop();
			}
		}
	}
}
void Elevator::pickUp(Floor& floors, int time) {
	size_t numPeeps = floors.size();//use size_t (switch it out for int and youll see why)
	for (int j = 0; j < numPeeps; j++) { //go through the number of people on the floor
		if (people.size() < MAX_CAPACITY) { //if the elevator is not full
			if ((people.empty()) || (floors.front().direction == direction)) {// and the person is going the same direction
				Person temp = floors.front(); //push them into the elevator
				floors.pop();
				temp.time_picked_up = time;
				people.push(temp);
			}
			else {
				floors.push(floors.front()); //go to the next person in line
				floors.pop();
			}
			if (floors.is_empty())
				break;
		}
	}
}
void Elevator::upOrDown(int& floorNum) {
	if (!people.empty()) {
		direction = people.front().direction;
		if (direction == 'u') //if the persons desired floor is up. Go up
			floorNum++;
		else//if its down. Go down.
			floorNum--;
	}
}
void Elevator::printReport(Person person, ofstream &report) { //Prints into a text file
	report << person.current_floor << '\t' << '\t' << person.desired_floor << '\t' << '\t' << person.time_picked_up
		<< '\t' << '\t' << person.time_dropped_off << endl;
	if ((person.time_dropped_off - person.time_picked_up) > longestWait)
		longestWait = person.time_dropped_off - person.time_picked_up;
}