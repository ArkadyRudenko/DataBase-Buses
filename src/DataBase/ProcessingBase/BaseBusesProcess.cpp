#include "BaseBusesProcess.h"
#include "StateListen.h"
#include "GetBusInfo.h"
#include "GetStopInfo.h"

using namespace std;
using namespace nlohmann;
using MapStates = unordered_map<string, shared_ptr<StateListen>>;

void BaseBusesProcess(BaseBuses &baseBuses, const json& stat_requests, ostream& os) {
    MapStates mapStates = CreateMapStates();
    json res;
    for(const auto& req : stat_requests) {
        res.push_back(mapStates[req["type"].get<string>()]->Listen(baseBuses, req, os));
    }
    os << res;
}

using namespace StateListening;

MapStates CreateMapStates() {
    MapStates mapStates;
    mapStates.insert({"Bus", make_shared<GetBusInfo>()});
    mapStates.insert({"Stop", make_shared<GetStopInfo>()});
    return mapStates;
}
