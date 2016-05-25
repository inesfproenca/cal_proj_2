#include "Helper.h"
#include <iostream>
#include <string>

using namespace std;

/**
 * @class User holds a user data and functionalities
 */
class User{
	static int ID;
	int userID;
	std::string name, address;
public:
    /**
     * Class base constructor
     */
	User(string name, string address);

    /**
     * @returns user ID
     */
	int getUserID() const {
		return userID;
	}

    /**
     * @returns user name
     */
	const string &getName() const {
		return name;
	}

    /**
     * @returns user address
     */
	const string &getAddress() const {
		return address;
	}

	friend bool operator==(const User &u1,const User &u2){
		return u1.userID == u2.userID;
	}

	friend ostream& operator<<(ostream& os, const User& u) {
		os << u.name << " " << u.address <<endl;
		return os;
	}

};





