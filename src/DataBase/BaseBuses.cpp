#include <sstream>
#include <algorithm>
#include <optional>
#include <map>

#include "BaseBuses.h"
#include "CalcDistance.h"

using namespace std;
//namespace rng = std::ranges;


void BaseBuses::AddStop(const BusStop &busStop) {
    if (auto it = name_in_stop.find(busStop.name); it != name_in_stop.end()) { // bad process
        it->second.SplitTwoMaps(busStop.getLengths());
        it->second.SetCoordinates(busStop.latitude, busStop.longitude);
    } else {
        name_in_stop.insert({busStop.name, busStop});
    }
    stop_in_buses.insert({busStop.name, {}});

    const auto &lengths = busStop.getLengths();
    for (const auto &stop: lengths) {
        if (auto other_stop = name_in_stop.find(stop.first); other_stop != name_in_stop.end()) {
            other_stop->second.AddLength({busStop.name, stop.second});
        } else {
            BusStop new_bus_stop(stop.first, -181, -181); // later will be new values, other_stop`s tmp
            new_bus_stop.AddLength({busStop.name, stop.second});
            name_in_stop.insert({stop.first, new_bus_stop});
        }
    }
}


void BaseBuses::AddBus(const string& bus,
                       const vector<string>& stops, Route route) {
    StopsList busInfoList;

    for (auto &stop: stops) {
        stop_in_buses.find(stop)->second.insert(bus);
        busInfoList.push_back(make_shared<BusStop>(
                name_in_stop.find(stop)->second
        ));
    }
    buses.insert({bus, BusInfo(move(busInfoList), route)});
}

optional<const set<string>> BaseBuses::GetInfoStop(const string &stop) {
    if (auto it = stop_in_buses.find(stop); it == stop_in_buses.end()) {
        return nullopt;
    } else {
        return it->second; // copy
    }
}

optional<const BusInfo> BaseBuses::GetInfoBus(const string &bus) {
    if (auto it = buses.find(bus); it == buses.end()) {
        return nullopt;
    } else {
        return it->second; // copy
    }
}