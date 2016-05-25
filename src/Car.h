#include <string>
#include  <sstream>
using namespace std;

class Car{
	int capacity;
	string licensePlate, brand;

public:
	Car(){capacity =0;};
	Car(int capacity, string licensePlate, string brand);
	int returnCapacity();
	void setCapacity(int cap);

	friend ostream& operator<<(ostream& os, const Car& c)
	{
	    os << c.brand << " holds up to " << c.capacity << endl;
	    return os;
	}
};



