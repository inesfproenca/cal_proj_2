/*
 * RideOffer.h
 *
 *  Created on: 20/04/2016
 *      Author: Ines
 */

#ifndef SRC_RIDEOFFER_H_
#define SRC_RIDEOFFER_H_

#include "Ride.h"
#include "RideRequest.h"
#include "Crossroad.h"
#include "Graph.h"
#include <list>

class RideOffer: public Ride {
private:
	std::list<unsigned int> route;
	vector<RideRequest> requests;
public:
	RideOffer(uint departurePlace, uint arrivalPlace, time_t departureTime, time_t departureTolerance, time_t arrivalTolerance, int noSeats, User* driver);
	virtual ~RideOffer();

	void decreaseNoSeats(uint noSeats);

    const vector<RideRequest>& getRequests() const {
        return requests;
    }

    const std::list<unsigned int>& getRoute() const {
        return route;
    }

    void setRoute(const std::list<unsigned int>& route) {
        this->route = route;
    }

    void addRequest(RideRequest request);

    bool findDestinationInPath(string dest);

    bool findPassenger(string name);
};

#endif /* SRC_RIDEOFFER_H_ */
