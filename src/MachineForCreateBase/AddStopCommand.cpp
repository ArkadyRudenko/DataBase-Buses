#include <cassert>

#include "AddStopCommand.h"
#include "BaseBuses.h"

using namespace std;
using namespace Json;

void AddStopCommand::Execute(BaseBuses &baseBuses,
                             const map<string, Node>& stop) {
    BusStop busStop(stop.at("name").AsString(),
                    stop.at("latitude").AsDouble(),
                    stop.at("longitude").AsDouble());
    try {
        busStop.setLengths(CreateMapStops(stop.at("road_distances").AsMap()));
    } catch (out_of_range& exp) {}

    baseBuses.AddStop(busStop);
}

unordered_map<string, int> CreateMapStops(const map<string, Node> &stops) {
    unordered_map<string, int> res;
    for (const auto&[key, value]: stops) {
        assert(value.AsInt() >= 0);
        res.insert({key, value.AsInt()});
    }
    return res;
}