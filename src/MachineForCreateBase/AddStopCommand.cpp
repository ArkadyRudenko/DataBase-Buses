#include "iomanip"

#include "AddStopCommand.h"
#include "BaseBuses.h"
#include "PasreRequests.h"

using namespace std;
using namespace Json;

void AddStopCommand::Execute(BaseBuses &baseBuses,
                             const map<string, Node>& stop) {
//    cout << stop.at("latitude").AsDouble() << "  " <<
//            stop.at("longitude").AsDouble() << '\n';
    BusStop busStop(stop.at("name").AsString(),
                    stop.at("latitude").AsDouble(),
                    stop.at("longitude").AsDouble());
    try {
        busStop.setLengths(CreateMapStops(stop.at("road_distances").AsMap()));
    } catch (out_of_range& exp) {
    }

    baseBuses.AddStop(busStop);
}

unordered_map<string, int> CreateMapStops(const map<string, Node> &stops) {
    unordered_map<string, int> res;
    for (const auto&[key, value]: stops) {
        res.insert({key, value.AsInt()});
    }
    return res;
}