#include "Floor.h"

void Floor::createFloor(int floorNum) {
	int numPeeps = (rand() % (MAX_CAPACITY / 2)); //Creates a random number of people on each floor.
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