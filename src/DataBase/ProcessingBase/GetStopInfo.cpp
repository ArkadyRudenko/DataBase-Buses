#include <sstream>

#include "GetStopInfo.h"
#include "PasreRequests.h"

using namespace std;
using namespace nlohmann;

namespace StateListening {
    json GetStopInfo::Listen(BaseBuses &baseBuses, const json &stop, std::ostream &os) {
        json set_stops;
        json stop_info;
        if (const auto stops = baseBuses.GetInfoStop(stop["name"])) {
            if (stops->size() != 0) {
                for (const auto &str: *stops) {
                    set_stops.push_back(str);
                }
                stop_info["buses"] = set_stops;
            } else {
                stop_info["buses"] = json::array();
            }
        } else {
            stop_info["error_message"] = "not found";
        }

        stop_info["request_id"] = stop["id"].get<int>();

        return stop_info;
    }
}