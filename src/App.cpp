#include "App.h"
#include "RideRequest.h"
#include "RideOffer.h"

void App::readDataRides(string filename) {
    ifstream in;
    string file = filename;
    in.open(file.c_str(), ios::in);
    if (in.good()) {
        while (in.good()) {
            int ID, departNode, arrivalNode,noseats;
            time_t departure, departTolerance,arrivalTolerance;
            string dummy;

            getline(in, dummy, '-');
            if (dummy == "<") {
                getline(in, dummy, '_');
                ID = atoi(dummy.c_str());

                getline(in, dummy, '_');
                departNode = atoi(dummy.c_str());


                getline(in, dummy, '_');
                arrivalNode =atoi(dummy.c_str());


                getline(in, dummy, '_');
                departure = atoi(dummy.c_str());


                getline (in, dummy, '_');
                departTolerance = atoi(dummy.c_str());


                getline(in, dummy, '_');
                arrivalTolerance = atoi(dummy.c_str());


                getline(in, dummy, '>');
                noseats = atoi(dummy.c_str());

				for (unsigned i = 0; i < users.size();i++){
					if((users[i])->getUserID() == ID){
					addRideRequest( users.at(i) ,departNode,arrivalNode, departure, departTolerance, arrivalTolerance, noseats);
					}
				}


            }

            if (!in.eof())
                in.ignore(1000, '\n');

            if (in.eof()) {
                return;
            }

        }
    }
    if (in.fail())
        throw FileReadingError();



    in.close();
}


void App::readData(string filename) {
    ifstream in;
    in.open(filename.c_str(), ios::in);
    if (in.good()) {
        while (in.good()) {
            string dummy;
            string name, address, licensePlate, brand;
            int capacity;

            getline(in, dummy, '-');

            if (dummy == "<") {
                getline(in, name, '_');
                getline(in, address, '>');

                addUser(name, address);
            }
            if (!in.eof())
                in.ignore(1000, '\n');

            if (in.eof()) {
                return;
            }

        }
    }
    if (in.fail())
        throw FileReadingError();

    in.close();
}

void App::addUser(string name, string address){
    User* u1 = new User(name,address);
    users.push_back(u1);
};

vector <User*> App::getUsers(){
    return users;
};

void App::addRideRequest(User* user , uint departurePlace, uint arrivalPlace, time_t departureTime, time_t departureTolerance, time_t arrivalTolerance, int noSeats){
    Ride* r = new RideRequest(departurePlace, arrivalPlace, departureTime,departureTolerance,arrivalTolerance, noSeats, user);
    if(!tryToMatchRide(r))
    	requests.push_back(r);
};

void App::addRideOffer(User* user , uint departurePlace, uint arrivalPlace, time_t departureTime, time_t departureTolerance, time_t arrivalTolerance, int noSeats){
    Ride* r = new RideOffer(departurePlace, arrivalPlace, departureTime, departureTolerance,arrivalTolerance, noSeats, user);
    offers.push_back(r);
    tryToMatchRide(r);
}

void App::showUsersInfo() {
    for(size_t i = 0; i < users.size(); i++){
        cout << "Id: " << users[i]->getUserID() << endl;
        cout << "\tName: " << users[i]->getName() <<endl;
        cout << "\tAddress: " << users[i]->getAddress() << endl;
    }
}

void App::showOffersInfo() {
    for(size_t i = 0; i < offers.size(); i++){
        cout << *dynamic_cast<RideOffer*>(offers[i]) << endl;
    }
}

void App::showRequestsInfo() {
    for(size_t i = 0; i < requests.size(); i++){
        cout << *dynamic_cast<RideRequest*>(requests[i]) << endl;
    }
}

void App::showAllInfo(){
	cout << "Users:\n";
	showUsersInfo();
	cout << "-----------------------\n";
	cout << "Offers:\n";
	showOffersInfo();
	cout << "-----------------------\n";
	cout << "Unmatched requests:\n";
	showRequestsInfo();
}

bool isPossible(RideOffer offer, RideRequest request,list<uint> route, list<double> dist){
    time_t srcTime, destTime;
    time_t arrivalTime = request.getDepartureTime() - offer.getDepartureTime();
    uint newSrc = request.getDeparturePlace();
    uint newDest = request.getArrivalPlace();

    list<uint>::iterator itr = route.begin();
    list<double>::iterator itd = dist.begin();

    while(itr != route.end() && itd != dist.end()){
        if(newSrc == *itr)
            srcTime = (time_t)(*itd / velAvr);
        if(newDest == *itr)
            destTime = (time_t)(*itd / velAvr);

        itr++;
        itd++;
    }

    return ((srcTime >(arrivalTime - request.getDepartureTolerance()) && srcTime <(arrivalTime + request.getDepartureTolerance())) &&
            ((destTime - srcTime) > request.getEstimatedArrival() - request.getArrivalTolerance()) && (destTime - srcTime < request.getEstimatedArrival() + request.getArrivalTolerance()));
}

bool App::matchRides(RideOffer &offer, RideRequest &request){

    if(offer.getNoSeats() < request.getNoSeats()){
        return false;
    }

    RoadMap* rm = RoadMap::getInstance();

    list<uint> newPath = offer.getRoute();
    list<double> dist;

    rm->bestPath(request.getDeparturePlace(), request.getArrivalPlace(), newPath, dist);


    if(isPossible(offer, request,newPath, dist)){
        vector<RideRequest> requests = offer.getRequests();

        for (int i = 0; i < requests.size(); ++i) {
            if(!isPossible(offer, requests[i],newPath, dist))
                return false;
        }

        offer.decreaseNoSeats(request.getNoSeats());

        offer.addRequest(request);
        offer.setRoute(newPath);
        return true;
    }
    else
        return false;
}

bool App::tryToMatchRide(Ride* newRide){

    RoadMap* rm = RoadMap::getInstance();
    bool found = false;

    if (dynamic_cast<RideOffer*>(newRide) == NULL){
        RideRequest* newRequest = dynamic_cast<RideRequest*>(newRide);
        for (int i = 0; i < offers.size(); ++i) {
            RideOffer* offer = dynamic_cast<RideOffer*>(offers[i]);
            if(matchRides(*offer,*newRequest)){
                cout << "Match found!!!" << endl;
                rm->visualizePath(offer->getRoute());
                return true;
            }
        }
    }


    if (dynamic_cast<RideRequest*>(newRide) == NULL){
        RideOffer* newOffer = dynamic_cast<RideOffer*>(newRide);
        for (int i = 0; i < requests.size(); ++i) {
            RideRequest* request = dynamic_cast<RideRequest*>(requests[i]);
            if(matchRides(*newOffer,*request)){
                requests.erase(requests.begin()+i);
                found = true;
                cout << "Match found!!!" << endl;
            }
        }
        rm->visualizePath(newOffer->getRoute());
    }

    return found;
}
