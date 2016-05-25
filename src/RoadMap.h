/*
 * Map.h
 *
 *  Created on: 16/04/2016
 *      Author: Ines
 */

#ifndef MAP_H_
#define MAP_H_

#include "Graph.h"
#include "Road.h"
#include "Crossroad.h"
#include "GraphViewer.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <map>

typedef unsigned int uint;

class Road;

/**
 * @class RoadMap represents a Road Map
 */
class RoadMap : protected Graph<Crossroad> {
private:
    map<uint, Crossroad> crossRoads;
    map<uint, Road> roads;

    float latitude_min;
    float longitude_min;
    float longitude_max;
    float latitude_max;

    /**
     * Reads nodes file
     */
    void readNodesFile(const std::string &fnodes);

    /**
     * Reads roads file
     */
    void readRoadsFile(const std::string &froads);

    /**
     * Reads subRoads file
     */
    void readSubRoadsFile(const std::string &fsubroads);

    GraphViewer *gv;
    static bool instanceFlag;
    static RoadMap *rm;

    /**
     * Class base constructor
     */
    RoadMap(const std::string &fnodes, const std::string &froads, const std::string &fsubroads);

    /**
     * Resets map to its inicial condition
     */
    void resetMap();
public:

    /**
     * Shows the map on the screen
     */
    void viewMap();

    /**
     * Finds the best path given the current path and new 2 points
     */
    void bestPath(uint newSrc, uint newDest, list<uint> &oldPath, list<double> &dist);

    /**
     * Inserts the new destination to pass by on the existing path
     */
    bool insertNewDest(uint id_src, uint id_dest, list<uint> mustPass, list<uint> &path, list<double> &dist);

    /**
     * Inserts the new point to pick-up a user to pass by on the existing path
     */
    void insertNewSrc(uint srcId, uint destId, uint newSrc, list<uint> &mustPass, list<uint> &path, list<double> &dist);

    /**
     * Given an address and door number, returns the crossroad id
     */
    uint getCrossroadIdFromAddress(string roadName, double doorNumber);

    /**
     * Given an id, checks if there is a crossroad with that id
     */
    bool validCrossroadId(uint id);

    /**
     * @returns the distance between two inodes
     */
    double getDist(uint srcId, uint destId);

    /**
     * Shows the given path on the graphviewer
     */
    void visualizePath(list<uint> path);

    static RoadMap *getInstance();

    /**
     * Default class destructor
     */
    ~RoadMap();
};

#endif /* SRC_MAP_H_ */
