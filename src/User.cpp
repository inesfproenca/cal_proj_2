#include "User.h"


using namespace std;

int User::ID = 0;

User::User(string name,string address){
	this->name = name;
	this->address = address;
	userID = ID;
	ID++;
}