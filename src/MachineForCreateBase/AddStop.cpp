#include "AddStop.h"

using namespace std;

void AddStop::Execute(BaseBuses &buses, std::istream &is) {
    string name_stop;
    getline(is, name_stop, ':');
    is.ignore(1);
    name_stop.erase(0,1);
    double latitude, longitude;
    is >> latitude;
    if (is.peek() != ',') {
        throw logic_error("Expected ,"); // TODO
    }
    is.ignore(1);
    is >> longitude;
    buses.AddStop({name_stop, latitude, longitude});


#ifdef TEST
    cout << "Stop Name = "<< name_stop << "\n";
    cout << "lat= " << latitude << "\n" <<
    "long = " << longitude << "\n";
#endif

}
