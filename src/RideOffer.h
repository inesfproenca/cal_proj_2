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

/**
 * @class RideRequest holds information of ride offers
 */
class RideOffer: public Ride {
private:
	std::list<unsigned int> route;
	vector<RideRequest> requests;
public:
    /**
      * Class base constructor
      */
	RideOffer(uint departurePlace, uint arrivalPlace, time_t departureTime, time_t departureTolerance, time_t arrivalTolerance, int noSeats, User* driver);

    /**
      * Class default destructor
      */
	virtual ~RideOffer();

    /**
     * Decreases the number of seats by the given number
     * @param noSeats number of seats to remove
     */
	void decreaseNoSeats(uint noSeats);

    /**
     * @returns the requests vector
     */
    const vector<RideRequest>& getRequests() const {
        return requests;
    }

    /**
     * @returns the route list
     */
    const std::list<unsigned int>& getRoute() const {
        return route;
    }

    /**
     * Sets the route to the given list
     * @param new route to set on the ride offer
     */
    void setRoute(const std::list<unsigned int>& route) {
        this->route = route;
    }

    /**
     * Adds a ride request to the requests vector
     * @param request ride request to add to the vector
     */
    void addRequest(RideRequest request);

    /**
     * Looks for the destination string name (or an approximation) on the itinerary list
     * @param dest destination name string
     * @returns the distance between the most similar string and the given string or -1 if it exceeds the tolerance
     */
    int findDestinationInPath(string dest);

    /**
     * Looks for the given name (or an approximation) on the list of people that will ride the vehicle (driver + hitchhikers)
     * @param name passenger name string
     * @returns the distance between the most similar string and the given string or -1 if it exceeds the tolerance
     */
    int findPassenger(string name);

    friend ostream& operator<<(ostream& os, const RideOffer& offer);
};

#endif /* SRC_RIDEOFFER_H_ */
