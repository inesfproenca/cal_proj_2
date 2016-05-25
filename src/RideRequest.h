/*
 * RideRequest.h
 *
 *  Created on: 20/04/2016
 *      Author: In�s
 */

#ifndef SRC_RIDEREQUEST_H_
#define SRC_RIDEREQUEST_H_

#include "Ride.h"

/**
 * @class RideRequest holds information of ride requests
 */
class RideRequest : public Ride {
private:

public:
    /**
     * Class base constructor
     */
    RideRequest(uint departurePlace, uint arrivalPlace, time_t departureTime, time_t departureTolerance,
                time_t arrivalTolerance, int noSeats, User *hitchhiker);

    /**
     * Class default destructor
     */
    virtual ~RideRequest();
};

#endif /* SRC_RIDEREQUEST_H_ */
