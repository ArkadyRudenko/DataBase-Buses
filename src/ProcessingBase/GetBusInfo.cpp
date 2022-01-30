#include <sstream>
#include <iomanip>

#include "GetBusInfo.h"

namespace StateListening {
    using namespace Json;
    using namespace std;

    void GetBusInfo::Listen(BaseBuses &baseBuses, const map<string, Node> &id_bus, ostream &os) {
        Node res;
        res.push_back("request_id"s, id_bus.at("id").AsInt());
        if (const auto bus_from_base = baseBuses.GetInfoBus(id_bus.at("name").AsString())) {
            res.push_back("route_length"s, bus_from_base->getRealLength());
            res.push_back("curvature"s, bus_from_base->getCurvature());
            res.push_back("stop_count"s, bus_from_base->GetCountStops());
            res.push_back("unique_stop_count"s, bus_from_base->getCountUniqueStops());
        } else {
            res.push_back("error_message"s, "not found"s);
        }
        os << res;
    }
}