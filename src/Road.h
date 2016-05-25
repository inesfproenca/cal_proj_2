/*
 * Road.h
 *
 *  Created on: 16/04/2016
 *      Author: Ines
 */

#ifndef SRC_ROAD_H_
#define SRC_ROAD_H_

#include <string>
#include "Crossroad.h"

/**
 * @class Road holds information a given real world road
 */
class Road{
private:
	string name;
	bool twoWay;
	vector<double> aproximateDoorNumbers;
	vector<Crossroad*> crossroads;
public:
    /**
     * Class base constructor
     */
	Road(string name, bool twoWay): name(name), twoWay(twoWay){}

    /**
     * @returns the road name
     */
	const string& getName() const {
		return name;
	}

    /**
     * @returns true if the road can be travelled in both directions, false if it can't
     */
	bool isTwoWay() const {
		return twoWay;
	}

    /**
     * Adds a crossroad to the road
     * @param c given crossroad
     */
	void addCrossroad(Crossroad* c){
		if(crossroads.empty()){
			aproximateDoorNumbers.push_back(0);
			crossroads.push_back(c);
		}
		else if(crossroads.back()->getId() != c->getId()){
			aproximateDoorNumbers.push_back(aproximateDoorNumbers.back() + crossroads.back()->getDist(*c));
			crossroads.push_back(c);
		}
	}

    /**
     * @returns the vector of crossroads
     */
	vector<Crossroad*> getCrossroads(){
		return crossroads;
	}

    /**
     * Gets node id for a given road name and door number
     * @param roadName given road name
     * @param doorNumber given door number
     * @returns node id
     */
	unsigned int getNodeId(string roadName, double doorNumber){
		if(roadName != name)
			return -1;

		unsigned int id =crossroads.front()->getId();
		double dist = doorNumber;

		for (int i = 0; i < aproximateDoorNumbers.size(); ++i) {
			double dist_tmp = abs(doorNumber - aproximateDoorNumbers[i]);
			if(dist_tmp < dist){
				dist = dist_tmp;
				id = crossroads[i]->getId();
			}
		}

		return id;
	}
};


#endif /* SRC_ROAD_H_ */
