#include <sstream>

#include "GetStopInfo.h"

using namespace std;
using namespace Json;

namespace StateListening {
    void GetStopInfo::Listen(BaseBuses &baseBuses,
                             const map<string, Node>&id_stop, ostream &os) {
        stringstream ss;
        Node res;
        if (const auto stop_from_base = baseBuses.GetInfoStop(id_stop.at("name").AsString())) {
            ss << "{\n";
            ss << R"("buses": [)";
            int i = 0, size = stop_from_base->size();
            for (const auto &stop: *stop_from_base) {
                ss << "\""<< stop << "\"";
                if (i != size - 1) {
                    ss << ", ";
                }
                i++;
            }
            ss << "]\n";
            ss << R"("request_id":)" << id_stop.at("id").AsInt();
            ss << "}\n";
        } else {
            ss << "{";
            ss << R"("request_id":)";
            ss << id_stop.at("id").AsInt();
            ss << R"(, "error_message": "not found")";
            ss << "}";
        }
        res = Load(ss).GetRoot();
        os << res;
    }
}