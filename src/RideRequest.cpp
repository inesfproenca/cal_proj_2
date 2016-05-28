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

ostream& operator<<(ostream& os, const RideRequest& request){

	struct tm * date = localtime(&request.departureTime);

	os << "Requested by:\n";
	for (int i = 0; i < request.hitchhikers.size(); ++i) {
		os << "\t" << request.hitchhikers.at(i)->getName() << endl;
	}

	os << "From: " << request.departurePlace << endl;
	os << "To:" << request.arrivalPlace << endl;

	os << "Departure time: " <<asctime(date);

	os << "Number of seats required : " << request.noSeats << endl;
	return os;
}
