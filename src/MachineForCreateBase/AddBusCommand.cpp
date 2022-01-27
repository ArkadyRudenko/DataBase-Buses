#include <sstream>
#include <vector>

#include "AddBusCommand.h"

using namespace std;
using namespace Json;

void AddBusCommand::Execute(BaseBuses &baseBuses, const map<string, Node>& bus) {
    baseBuses.AddBus(bus.at("name").AsString(),
                     CreateVectorStops(bus.at("stops")),
                     GetRoute(bus.at("is_roundtrip")));
}

vector<string> CreateVectorStops(const Node &stops) {
    vector<string> res;
    for (const auto &stop: stops.AsArray()) {
        res.push_back(stop.AsString());
    }
    return res;
}

Route GetRoute(const Json::Node& route) {
    return route.AsBool() ? Route::ANNULAR : Route::STRAIGHT;
}