/*
 * Crossroad.h
 *
 *  Created on: 16/04/2016
 *      Author: Ines
 */

#ifndef SRC_CROSSROAD_H_
#define SRC_CROSSROAD_H_

#include <cmath>

/**
 * @class Crossroad represents a map node and functionalities related to it
 */
class Crossroad{
    unsigned int id;
    float latitude_in_degrees;
    float longitude_in_degrees;
    float longitude_in_radians;
    float latitude_in_radians;
public:

    /**
     * Class Base Constructor
     */
    Crossroad(unsigned int id, float lat_d, float lon_d, float lon_r, float lat_r): id(id), latitude_in_degrees(lat_d),
                                                                                    longitude_in_degrees(lon_d), longitude_in_radians(lon_r), latitude_in_radians(lat_r){}

    /**
     * @returns Crossroad latitude (in degrees)
     */
    float getLatitudeInDegrees() const {
        return latitude_in_degrees;
    }

    /**
     * @returns Crossroad latitude (in radians)
     */
    float getLatitudeInRadians() const {
        return latitude_in_radians;
    }

    /**
     * @returns Crossroad longitude (in degrees)
     */
    float getLongitudeInDegrees() const {
        return longitude_in_degrees;
    }

    /**
     * @returns Crossroad longitude (in radians)
     */
    float getLongitudeInRadians() const {
        return longitude_in_radians;
    }

    bool operator == (const Crossroad &c2) const{
        return id == c2.id;
    }

    /**
     * Calculates the distance between 2 crossroads
     * @param c2 crossroad to calculate distance to
     * @returns distance between this and another crossroad
     */
    double getDist(Crossroad c2){
        int R = 6371000; // metres
        double lat1 = latitude_in_radians;
        double lat2 = c2.latitude_in_radians;
        double deltaLat = lat2 - lat1;
        double deltaLon = c2.longitude_in_radians - longitude_in_radians;

        double a = sin(deltaLat/2) * sin(deltaLat/2) +
                   cos(lat1) * cos(lat2) *
                   sin(deltaLon/2) * sin(deltaLon/2);
        double c = 2 * atan2(sqrt(a), sqrt(1-a));

        return (R * c);
    }

    /**
     * @returns crossroad id
     */
    unsigned int getId() const {
        return id;
    }
};


#endif /* SRC_CROSSROAD_H_ */
