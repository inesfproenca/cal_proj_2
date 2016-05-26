/*
 * Ride.h
 *
 *  Created on: 20/04/2016
 *      Author: Ines
 */

#ifndef SRC_RIDE_H_
#define SRC_RIDE_H_

#include <ctime>
#include <memory>
#include "RoadMap.h"
#include "User.h"

const double velAvr = 50000 / 3600; //50km/h in m/s

/**
 * @class Ride superclass for ride requests, offers and completed rides
 */
class Ride {
protected:
    //Como saber o tempo dispendido
    uint departurePlace, arrivalPlace;
    time_t departureTime, estimatedArrival, departureTolerance, arrivalTolerance;
    int noSeats;
    User *driver;
    vector<User *> hitchhikers;
public:
    /**
     * Class default Constructor
     */
    Ride() { };

    /**
     * Class base constructor
     */
    Ride(uint departurePlace, uint arrivalPlace, time_t departureTime, time_t departureTolerance,
         time_t arrivalTolerance, int noSeats);

    /**
     * Class default destructor
     */
    virtual ~Ride();

    /**
     * @returns tolerance time for arrival
     */
    time_t getArrivalTolerance() const {
        return arrivalTolerance;
    }

    /**
     * @returns departure date
     */
    time_t getDepartureTime() const {
        return departureTime;
    }

    /**
     * @returns tolerance time for departure
     */
    time_t getDepartureTolerance() const {
        return departureTolerance;
    }

    /**
     * @returns estimated time of arrival
     */
    time_t getEstimatedArrival() const {
        return estimatedArrival;
    }

    /**
     * @returns number of seats
     */
    int getNoSeats() const {
        return noSeats;
    }

    /**
     * @returns place of arrival (inode)
     */
    uint getArrivalPlace() const {
        return arrivalPlace;
    }

    /**
     * @returns place of departure (inode)
     */
    uint getDeparturePlace() const {
        return departurePlace;
    }

    /**
     * @returns vector of hitchhikers
     */
	const vector<User*>& getHitchhikers() const {
		return hitchhikers;
	}
};

#endif /* SRC_RIDE_H_ */
