/*
 * Ride.cpp
 *
 *  Created on: 20/04/2016
 *      Author: Ines
 */

#include "Ride.h"

Ride::Ride(uint departurePlace, uint arrivalPlace, time_t departureTime, time_t departureTolerance, time_t arrivalTolerance, int noSeats):
departurePlace(departurePlace), arrivalPlace(arrivalPlace),departureTime(departureTime), departureTolerance(departureTolerance), arrivalTolerance(arrivalTolerance), noSeats(noSeats){
    RoadMap* rm = RoadMap::getInstance();

    estimatedArrival = (rm->getDist(departurePlace,arrivalPlace)/velAvr);
}

Ride::~Ride() {
	// TODO Auto-generated destructor stub
}

