#include "Handler.h"
#include "App.h"

bool validDay(int year, int month, int day) {
	switch (month) {
		case 4:
		case 6:
		case 9:
		case 11:
			return day <= 30;
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			return day <= 31;
		case 2: {
			bool leapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
			if (leapYear)
				return day <= 29;
			else
				return day <= 28;
		}
		default:
			return false;
	}
}

bool validHour(int hour, int minute) {
	return hour >= 0 && hour <= 23 && minute >= 0 && minute <= 59;
}

bool operator>(tm d1, tm d2){
	return mktime(&d1) > mktime(&d2);
}

bool operator==(tm d1, tm d2){
	return mktime(&d1) == mktime(&d2);
}

tm getToday(){
	time_t now = time(NULL);
	tm *today = localtime(&now);
	return *today;
}

bool readString(const string &prompt, string &returnString) {

	string testString;
	cout << prompt;
	getline(cin, testString);
	cout << endl;
	if (cin.fail()) {
		if (!cin.eof())
			cin.ignore(1000, '\n');
		cin.clear();
		return false;
	}
	if (testString == "" || testString == "\n")
		return false;
	returnString = testString;
	return true;
}

void getDate(tm &date) {
	string returnString = "";
	do {
		while (!readString("Please insert the starting date year: ", returnString)) {
			cout << "Please insert a valid starting date year" << endl;
		}
		date.tm_year = atoi(returnString.c_str()) - 1900;
		while (!readString("Please insert the starting date month: ", returnString)) {
			cout << "Please insert a valid starting date month" << endl;
		}
		date.tm_mon = atoi(returnString.c_str()) - 1;
		while (!readString("Please insert the starting date day: ", returnString)) {
			cout << "Please insert a valid starting date day" << endl;
		}
		date.tm_mday = atoi(returnString.c_str());

		if (!validDay(date.tm_year + 1900, date.tm_mon + 1, date.tm_mday))
			cout << "Invalid date! Insert a correct one: " << endl;

	} while (!validDay(date.tm_year + 1900, date.tm_mon + 1, date.tm_mday));
	do {
		while (!readString("Please insert the starting hour: ", returnString)) {
			cout << "Please insert a valid starting hour" << endl;
		}
		date.tm_hour = atoi(returnString.c_str());
		while (!readString("Please insert the starting minute: ", returnString)) {
			cout << "Please insert a valid starting minute" << endl;
		}
		date.tm_min = atoi(returnString.c_str());
		if (!validHour(date.tm_hour, date.tm_min))
			cout << "Invalid hour! Insert a correct one: " << endl;
	} while (!validHour(date.tm_hour, date.tm_min));
}

void createRide(App &a, int rideType){
	bool valid = false;
	bool validID = false;
	User* user = NULL;
	int ID;
	int timevar;
    int noSeats;
    uint src, dest;
    RoadMap* rm = RoadMap::getInstance();

	do {
		cout << "Introduce your personal ID: ";
		cin >> ID;
		vector <User*> users = a.getUsers();
		for (unsigned z = 0; z < users.size(); z++){
			if( (*users[z]).getUserID() == ID){
				validID = true;
				user = users[z];
			}
		}
	}while(!validID);


    do {
//        string roadName;
//        uint doorNumber;
//        RoadMap* rm = RoadMap::getInstance();
//
//        cout << "Introduce the name of the street of initial location: \n";
//        cin.ignore(10000,'\n');
//        getline(cin,roadName);
//        cout << roadName << "...." << endl;
//
//        cout << "Introduce the number of the door of initial location: \n";
//        cin >> doorNumber;
//        src = rm->getCrossroadIdFromAddress(roadName, doorNumber);
        cout << "Introduce the id of inicial location: \n";
        cin >> src;

    }while(!rm->validCrossroadId(src));

    //Input dest
    do {
//        string roadName;
//        uint doorNumber;
//        RoadMap* rm = RoadMap::getInstance();
//
//        cout << "Introduce the name of the street of final location: \n";
//        cin.ignore(10000,'\n');
//        getline(cin,roadName);
//        cout << roadName << "...."<< endl;
//
//        cout << "Introduce the number of the door of final location: \n";
//        cin >> doorNumber;
//
//        dest = rm->getCrossroadIdFromAddress(roadName, doorNumber);
        cout << "Introduce the id of final location: \n";
        cin >> dest;
    }while(!rm->validCrossroadId(dest));

    if(rideType == 1)
        cout << "Please insert the number of free seats on your car: ";
    else
        cout << "Please insert the number of seats you are requesting: ";
    cin >> noSeats;

	tm date;
	do {
		cin.ignore();
		getDate(date);
		tm today = getToday();
		if (today >date) {
			cout << "Invalid date, please choose a date after today.";
		}
		else {
			cout << date.tm_mday << "/" << date.tm_mon+1 << "/" << date.tm_year+1900 << endl;
			valid = true;
		}
	}while(!valid);

	cout <<"Introduce tolerance for your departure in minutes: ";
	cin >> timevar;
	time_t departureTolerance= timevar *60;

	cout <<"Introduce tolerance for your arrival in minutes: ";
	cin >> timevar;
	time_t arrivalTolerance = timevar *60;

    if(user != NULL) {
        if (rideType == 1)
            a.addRideOffer(user, src, dest, mktime(&date), departureTolerance, arrivalTolerance, noSeats);
        else
            a.addRideRequest(user, src, dest, mktime(&date), departureTolerance, arrivalTolerance, noSeats);
    }
};
