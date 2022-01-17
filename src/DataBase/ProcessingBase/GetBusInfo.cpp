#include "GetBusInfo.h"

namespace StateListening {

    void GetBusInfo::Listen(BaseBuses &buses, std::ostream &os, std::istream &is) {
        int id_bus;
        is >> id_bus;
        buses.GetInfoBus(id_bus, os);
    }
}