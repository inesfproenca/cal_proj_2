/*
 * RideCompleted.cpp
 *
 *  Created on: 20/04/2016
 *      Author: Ines
 */

#include "RideCompleted.h"

RideCompleted::RideCompleted(RideOffer* rideOffer): rideOffer(rideOffer), rideRequests(rideOffer->getRequests()){
}

RideCompleted::~RideCompleted() {
	// TODO Auto-generated destructor stub
}

