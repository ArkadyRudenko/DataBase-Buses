#include <sstream>

#include "GetStopInfo.h"
#include "StateListen.h"

namespace Requests {
    using namespace std;
    using namespace Json;
    Node GetStopInfo::Listen(BaseBuses &baseBuses,
                                   const map<string, Node> &id_stop) {
        Dict dict;
        dict["request_id"] = id_stop.at("id").AsInt();
        if (const auto stop_from_base = baseBuses.GetInfoStop(id_stop.at("name").AsString())) {
            Node buses;
            for (const auto &stop: *stop_from_base) {
                buses.push_back(stop);
            }
            dict["buses"] = move(buses);

        } else {
            dict["error_message"] = "not found";
        }
        return Node(dict);
    }
}