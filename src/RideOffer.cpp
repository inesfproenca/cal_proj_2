/*
 * RideOffer.cpp
 *
 *  Created on: 20/04/2016
 *      Author: Ines
 */

#include "RideOffer.h"

RideOffer::RideOffer(uint departurePlace, uint arrivalPlace, time_t departureTime, time_t departureTolerance, time_t arrivalTolerance, int noSeats, User* driver):
	Ride(departurePlace, arrivalPlace, departureTime, departureTolerance, arrivalTolerance, noSeats){

	route.push_back(departurePlace);
    route.push_back(arrivalPlace);

    this->driver = driver;
}

void RideOffer::decreaseNoSeats(uint noSeats){
    this->noSeats -= noSeats;
}

RideOffer::~RideOffer() {
	// TODO Auto-generated destructor stub
}

