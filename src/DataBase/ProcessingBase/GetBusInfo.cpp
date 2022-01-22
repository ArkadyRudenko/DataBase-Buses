#include <cmath>

#include "GetBusInfo.h"
#include "PasreRequests.h"

namespace StateListening {
    using namespace nlohmann;
    using namespace std;
    json GetBusInfo::Listen(BaseBuses& baseBuses, const json& bus, std::ostream& os) {
        json bus_info;
        if(const auto bus_from_base =  baseBuses.GetInfoBus(bus["name"].get<string>())) {
            bus_info["route_length"] = bus_from_base->getRealLength();
            bus_info["curvature"] = round(bus_from_base->getCurvature() * 100000)/100000;
            bus_info["unique_stop_count"] = bus_from_base->getCountUniqueStops();
            bus_info["stop_count"] = bus_from_base->GetCountStops();
        } else {
            bus_info["error_message"] = "not found";
        }
        bus_info["request_id"] = bus["id"].get<int>();
        return bus_info;
    }
}