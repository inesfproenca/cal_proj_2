/*
 * RideOffer.cpp
 *
 *  Created on: 20/04/2016
 *      Author: Ines
 */

#include "RideOffer.h"
#include <ctime>

RideOffer::RideOffer(uint departurePlace, uint arrivalPlace, time_t departureTime, time_t departureTolerance, time_t arrivalTolerance, int noSeats, User* driver):
Ride(departurePlace, arrivalPlace, departureTime, departureTolerance, arrivalTolerance, noSeats){

	route.push_back(departurePlace);
	route.push_back(arrivalPlace);

	this->driver = driver;
}

void RideOffer::decreaseNoSeats(uint noSeats){
	this->noSeats -= noSeats;
}

void RideOffer::addRequest(RideRequest request){
	requests.push_back(request);

	vector<User*> newHitchikers = request.getHitchhikers();
	hitchhikers.insert(hitchhikers.end(), newHitchikers.begin(), newHitchikers.end());
}

RideOffer::~RideOffer() {
	// TODO Auto-generated destructor stub
}

//String matching functions
vector<int> prefixFunction(string toSearch){
	vector<int> prefix(toSearch.length());
	prefix[0] = -1;
	int k = -1;

	for(int i = 1; i < toSearch.length();i++){
		while(k>-1 && toSearch[k+1] != toSearch[i])
			k = prefix[k];

		if(toSearch[k+1] == toSearch[i])
			k++;

		prefix[i] = k;
	}

	return prefix;
}

/**
 * @returns number of times toSearch was found in texts
 */
int numStringMatching(vector<string> texts, string toSearch){
	int result = 0;
	vector<int> prefix = prefixFunction(toSearch);

	for (uint j = 0; j < texts.size(); ++j) {
		string text = texts[j];
		int q = -1;
		for(unsigned int i = 0; i < text.length();i++){
			while(q > -1 && toSearch[q+1] != text[i] && q != toSearch.length()-1)
				q = prefix[q];

			if(toSearch[q+1] == text[i])
				q++;

			if(q == toSearch.length()-1){
				result++;
				q = prefix[q];
			}
		}
	}

	return result;
}

int distanceBetweenTwoStrings(string str, string toSearch){
	vector<vector<int> > dist(toSearch.length()+1, vector<int>(str.length()+1));

	for(unsigned int i = 0; i <= toSearch.length(); i++)
		dist[i][0] = i;
	for(unsigned int j = 0; j <= str.length(); j++)
		dist[0][j] = j;

	for(unsigned int i = 1; i < dist.size(); i++)
		for(unsigned int j = 1; j < dist[0].size(); j++){
			if(toSearch[i-1] == str[j-1])
				dist[i][j] = dist[i-1][j-1];
			else
				dist[i][j] = 1 + min(dist[i-1][j-1], //Substituicao
						min(dist[i-1][j], 	//Insercao
								dist[i][j-1]));	//Eliminacao
		}


	return dist[toSearch.length()][str.length()];
}

/**
 * @returns minimum distance found between texts element and toSearch
 */
int numApproximateStringMatching(vector<string> texts, string toSearch){
	int minDist = -1;

	for (uint i = 0; i < texts.size(); ++i) {
		string str = texts[i];
		int dist = distanceBetweenTwoStrings(str, toSearch);

		if(minDist == -1)
			minDist = dist;
		else
			minDist = min(minDist, dist);
	}

	return minDist;
}

//TODO change tolerance
int RideOffer::findDestinationInPath(string dest){
	RoadMap* rm = RoadMap::getInstance();
	int tolerance = dest.size();

	vector<string> roadRoute = rm->getRoadsPassed(route);

	if(numStringMatching(roadRoute,dest) > 0)
		return 0;

	int minDist = numApproximateStringMatching(roadRoute,dest);
	if(minDist < tolerance)
		return minDist;

	return -1;
}

int RideOffer::findPassenger(string name){
	vector<string> passengerNames;
	int tolerance = name.size();

	passengerNames.push_back(driver->getName());

	for (uint i = 0; i < hitchhikers.size(); ++i) {
		passengerNames.push_back(hitchhikers[i]->getName());
	}

	if(numStringMatching(passengerNames,name) > 0)
		return 0;

	int minDist = numApproximateStringMatching(passengerNames,name);
	if(minDist < tolerance)
		return minDist;

	return -1;
}

ostream& operator<<(ostream& os, const RideOffer& offer)
{
	RoadMap* rm = RoadMap::getInstance();

	vector<string> roadRoute = rm->getRoadsPassed(offer.getRoute());

	struct tm * date = localtime(&offer.departureTime);

	os << "Offered by driver: " << offer.driver->getName() << endl;

	os << "Passengers:\n";
	for (int i = 0; i < offer.hitchhikers.size(); ++i) {
		os << "\t" <<offer.hitchhikers.at(i)->getName() << endl;
	}

	os << "From: " << offer.departurePlace << endl;
	os << "To:" << offer.arrivalPlace << endl;

	os << "Route:\n";
	for (int i = 0; i < roadRoute.size(); ++i) {
		os << "\t" << roadRoute.at(i) << endl;
	}

	os << "Departure time: " <<asctime(date);

	return os;
}

