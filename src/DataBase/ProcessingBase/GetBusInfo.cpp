#include "GetBusInfo.h"
#include "PasreRequests.h"

namespace StateListening {

    void GetBusInfo::Listen(BaseBuses &buses, std::ostream &os, std::istream &is) {
        std::string id_bus;
        getline(is, id_bus);
        buses.GetInfoBus(RemoveSpaces(id_bus), os);
    }
}