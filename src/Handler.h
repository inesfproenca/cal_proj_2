#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <utility>
#include <ctime>
#include "Exceptions.h"


using namespace std;


class App;

/**
 * Creates a ride request or offer and adds it to the given app
 * @param a app to add the ride to
 * @param rideType type of ride to add (offer or request)
 */
void createRide(App &a, int rideType);

/**
 * Checks if a given date is valid
 * @param year given date year
 * @param month given date month
 * @param day given date day of the month
 * @return true if the date is valid, false if it isn't
 */
bool validDay(int year, int month, int day);

/**
 * Checks if a given hour is valid
 * @param hour given hour
 * @param minute given minute
 * @return true if the hour is valid, false if it isn't
 */
bool validHour(int hour, int minute);

bool operator>(tm d1, tm d2);

bool operator==(tm d1, tm d2);

/**
 * Prompts the user to input a value and reads the given string by the user
 * @param prompt message prompt to ask the user for the input
 * @param returnString string inserted by the user
 */
bool readString(const string &prompt, string &returnString);

/**
 * Prompts the user to insert a full and valid date (including hour)
 * @param date date that gets altered by the user input
 */
void getDate(tm &date);
