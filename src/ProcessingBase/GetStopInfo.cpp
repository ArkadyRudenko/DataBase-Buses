#include <sstream>

#include "GetStopInfo.h"

using namespace std;
using namespace Json;

namespace StateListening {
    void GetStopInfo::Listen(BaseBuses &baseBuses,
                             const map<string, Node> &id_stop, ostream &os) {
        Node res;
        res.push_back("request_id"s, id_stop.at("id").AsInt());
        if (const auto stop_from_base = baseBuses.GetInfoStop(id_stop.at("name").AsString())) {
            Node buses;
            for (const auto &stop: *stop_from_base) {
                buses.push_back(stop);
            }
            res.push_back("buses"s, buses);

        } else {
            res.push_back("error_message"s, "not found"s);
        }
        os << res;
    }
}