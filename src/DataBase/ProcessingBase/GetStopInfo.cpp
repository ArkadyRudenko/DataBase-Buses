#include "GetStopInfo.h"
#include "PasreRequests.h"

using namespace std;

namespace StateListening {

    void GetStopInfo::Listen(BaseBuses &buses, std::ostream &os, std::istream &is) {
        string stop_name;
        getline(is, stop_name);
        buses.GetInfoStop(RemoveSpaces(stop_name), os);
    }
}