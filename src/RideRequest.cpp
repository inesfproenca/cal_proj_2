/*
 * RideRequest.cpp
 *
 *  Created on: 20/04/2016
 *      Author: Ines
 */

#include "RideRequest.h"

RideRequest::RideRequest(uint departurePlace, uint arrivalPlace,time_t departureTime, time_t departureTolerance, time_t arrivalTolerance, int noSeats, User* hitchhiker):
Ride(departurePlace, arrivalPlace, departureTime, departureTolerance, arrivalTolerance, noSeats){
    this->driver = NULL;
    this->hitchhikers.push_back(hitchhiker);
}

RideRequest::~RideRequest() {
	// TODO Auto-generated destructor stub
}

