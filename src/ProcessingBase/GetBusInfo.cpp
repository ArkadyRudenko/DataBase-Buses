#include <sstream>
#include <iomanip>

#include "GetBusInfo.h"

namespace Requests {
    using namespace Json;
    using namespace std;

    Node GetBusInfo::Listen(BaseBuses &baseBuses, const map<string, Node> &id_bus) {
        Dict dict;
        dict["request_id"] = id_bus.at("id").AsInt();
        if (const auto bus_from_base = baseBuses.GetInfoBus(id_bus.at("name").AsString())) {
            dict["route_length"] = bus_from_base->getRealLength();
            dict["curvature"] = bus_from_base->getCurvature();
            dict["stop_count"] = bus_from_base->GetCountStops();
            dict["unique_stop_count"] = bus_from_base->getCountUniqueStops();
        } else {
            dict["error_message"] = "not found";
        }
        return Node(dict);
    }
}