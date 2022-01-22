#include <map>

#include "AddStopCommand.h"
#include "BaseBuses.h"
#include "PasreRequests.h"

using namespace std;
using namespace nlohmann;

void AddStopCommand::Execute(BaseBuses &baseBuses, json &stop) {
    BusStop busStop(stop["name"].get<string>(),
                    stop["latitude"].get<double>(),
                    stop["longitude"].get<double>());
    busStop.setLengths(CreateMapStops(stop));
    baseBuses.AddStop(busStop);
}

unordered_map<string, int> CreateMapStops(const json &stops) {
    unordered_map<string, int> res;
    for (const auto&[key, value]: stops["road_distances"].get<map<string, int>>()) {
        res.insert({key, value});
    }
    return res;
}