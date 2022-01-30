#include "BaseBusesProcess.h"
#include "StateListen.h"
#include "GetBusInfo.h"
#include "GetStopInfo.h"

using namespace std;
using namespace Json;
using MapStates = unordered_map<string, shared_ptr<StateListen>>;

void BaseBusesProcess(BaseBuses &baseBuses, const Node& stat_requests, ostream& os) {
    MapStates mapStates = CreateMapStates();
    os << "[\n";
    bool is_begin = false;
    for(const auto& req : stat_requests.AsArray()) {
        if(is_begin) {
            os << ",\n";
        }
        mapStates[req.AsMap().at("type").AsString()]->Listen(baseBuses, req.AsMap(), os);
        is_begin = true;
    }
    os << "\n]";
}

using namespace StateListening;

MapStates CreateMapStates() {
    MapStates mapStates;
    mapStates.insert({"Bus", make_shared<GetBusInfo>()});
    mapStates.insert({"Stop", make_shared<GetStopInfo>()});
    return mapStates;
}
