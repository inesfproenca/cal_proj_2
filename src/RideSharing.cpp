#include "RoadMap.h"
#include "App.h"
#include "Handler.h"

using namespace std;

//TODO Pesquisar se o destino de uma pessoa (nome da rua) está incluído no percurso de um dado motorista (sequencia de ruas por ounde vai passar)
//TODO Procurar uma pessoa específica entre os ocupantes de uma dada viatura
//TODO Pesquisa dos nomes de ruas e de passageiros deverá ser exata e aproximada

int main(){
	RoadMap* rm = RoadMap::getInstance();
	rm->viewMap();

	string filename, road, name;
	App application;

	ifstream test;

	do{
		cout << "Introduce filename: ";
		getline(cin, filename);
		if(filename == ""){
			filename = "Database.txt";
			break;
		}
		test.open(filename.c_str());
		if(!test.is_open())
			cout << "File doesn't exist!" << endl;
	}while(!test.is_open());

	if(filename != "") {
		try {
			application.readData(filename);
		} catch (FileReadingError &e) {
			cout << "Error reading file." << endl;
			return 1;
		}
	}

	try {
		application.readDataRides("ridesDatabase.txt");
	} catch (FileReadingError &e) {
		cout << "Starting without RidesTest." << endl;
	}

	int choice, counter = 0;
	do{
		do{
			if (counter != 0){
				cout << "You have introduced an invalid option!\n" << endl;
			}
			cout << "5 - Find Passenger" << endl;
			cout << "4 - Find Destination" << endl;
			cout << "3 - View All Info" << endl;
			cout << "2 - Request Ride" << endl;
			cout << "1 - Offer Ride" << endl;
			cout << "0 - Exit Application" << endl;

			cout << "Choose appropriate numerical option: ";
			cin >> choice;
			counter ++;
		}while( (choice < 0) || (choice > 5));
		counter = 0;

		switch(choice){
		case 5:
			cin.ignore(1000,'\n');
			cout << "Please insert the name you wish to search: ";
			getline(cin,name);
			application.findAndPrintUserMatches(name);
			break;
		case 4:
			cin.ignore(1000,'\n');
			cout << "Please insert your destination: ";
			getline(cin,road);
			application.findAndPrintRoadMatches(road);
			break;
		case 3:
			application.showAllInfo();
			cout<<endl;
			break;
		case 2:
		case 1:
			createRide(application, choice);
			break;
		case 0:
			cout<<"Exiting..." << endl;
			return 0;
		default:
			return 3;
		}
	}while(1);
}
