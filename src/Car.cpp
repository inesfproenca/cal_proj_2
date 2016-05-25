#include "Car.h"


Car::Car(int capacity, string licensePlate, string brand){
	this->capacity = capacity;
	this->licensePlate = licensePlate;
	this->brand = brand;
}

void Car::setCapacity(int cap){
	capacity = cap;
}

int Car::returnCapacity(){
	return capacity;
}


