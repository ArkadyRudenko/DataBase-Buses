#include "BaseBusesProcess.h"
#include "StateListen.h"
#include "GetBusInfo.h"
#include "GetStopInfo.h"
#include "GetRouteInfo.h"
#include "GetMap.h"

using namespace std;
using namespace Json;
using MapStates = unordered_map<string, shared_ptr<Requests::StateListen>>;

Node BaseBusesProcess(BaseBuses &baseBuses, const Node &stat_requests) {
    MapStates mapStates = CreateMapStates();
    vector<Node> results;
    for (const auto &req: stat_requests.AsArray()) {

        results.push_back(move(
                mapStates[req.AsMap().at("type").AsString()]->Listen(baseBuses, req.AsMap())
        ));
    }
    return Node(results);
}

using namespace Requests;

MapStates CreateMapStates() {
    MapStates mapStates;
    mapStates.insert({"Bus", make_shared<GetBusInfo>()});
    mapStates.insert({"Stop", make_shared<GetStopInfo>()});
    mapStates.insert({"Route", make_shared<GetRouteInfo>()});
    mapStates.insert({"Map", make_shared<GetMap>()});
    return mapStates;
}
