#include <sstream>
#include <iomanip>

#include "GetBusInfo.h"
#include "PasreRequests.h"

namespace StateListening {
    using namespace Json;
    using namespace std;
    void GetBusInfo::Listen(BaseBuses& baseBuses, const map<string, Node>& id_bus, ostream& os) {
        stringstream ss;
        ss.setf(ios_base::fixed);
        Node res;
        if(const auto bus_from_base =  baseBuses.GetInfoBus(id_bus.at("name").AsString())) {
            ss << "{ \"route_length\": ";
            ss << bus_from_base->getRealLength();
            ss << R"(, "request_id":)";
            ss << to_string(id_bus.at("id").AsInt());
            ss << R"(, "curvature":)";
            ss << setprecision(30) << to_string(bus_from_base->getCurvature());
            ss << R"(, "stop_count":)";
            ss << bus_from_base->GetCountStops();
            ss << R"(, "unique_stop_count":)";
            ss << bus_from_base->getCountUniqueStops();
            ss << "}";
        } else {
            ss << "{";
            ss << R"("request_id":)";
            ss << id_bus.at("id").AsInt();
            ss << R"(, "error_message": "not found")";
            ss << "}";
        }
        res = Load(ss).GetRoot();
        os << res;
    }
}