#include "AddStop.h"
#include "BaseBuses.h"
#include "PasreRequests.h"

using namespace std;

void AddStop::Execute(BaseBuses &buses, std::istream &is) {
    string name_stop;
    getline(is, name_stop, ':');
    is.ignore(1);
    double latitude, longitude;
    is >> latitude;
    is.ignore(1);
    is >> longitude;

    if (is.peek() == ',') {
        is.ignore(1);
        string line;
        getline(is, line);
        BusStop busStop(move(RemoveSpaces(name_stop)), latitude, longitude);
        busStop.setLengths(getTokens(line));
        buses.AddStop(busStop);
        return;
    }
    BusStop busStop(move(RemoveSpaces(name_stop)), latitude, longitude);
    busStop.setLengths({});
    buses.AddStop(busStop);
}
