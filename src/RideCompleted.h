/*
 * RideCompleted.h
 *
 *  Created on: 20/04/2016
 *      Author: Ines
 */

#ifndef SRC_RIDECOMPLETED_H_
#define SRC_RIDECOMPLETED_H_

#include "RideOffer.h"
#include "RideRequest.h"
#include <vector>

/**
 * @class RideCompleted holds information of rides that were matched
 */
class RideCompleted{
	RideOffer* rideOffer;
	const vector<RideRequest> rideRequests;
public:
    /**
     * Class base constructor
     */
	RideCompleted(RideOffer* rideOffer);
    /**
     * Class default destructor
     */
	virtual ~RideCompleted();
};

#endif /* SRC_RIDECOMPLETED_H_ */
