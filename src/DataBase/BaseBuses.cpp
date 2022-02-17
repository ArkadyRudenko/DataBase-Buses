#include <cmath>
#include <sstream>
#include <algorithm>
#include <optional>
#include <memory>

#include "BaseBuses.h"
#include "TransportRouter.h"

using namespace std;

void BaseBuses::AddStop(const Stop &busStop) {
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
            Stop new_bus_stop(stop.first, -181, -181); // later will be new values, other_stop`s tmp
            new_bus_stop.AddLength({busStop.name, stop.second});
            name_in_stop.insert({stop.first, new_bus_stop});
        }
    }
}


void BaseBuses::AddBus(const string &bus,
                       const vector<string> &stops, Route route) {
    StopsList busInfoList;

    for (auto &stop: stops) {
        stop_in_buses.find(stop)->second.insert(bus);
        busInfoList.push_back(make_shared<Stop>(
                name_in_stop.find(stop)->second
        ));
    }
    buses.insert({bus, BusInfo(move(busInfoList), route)});
}

optional<const set<string>> BaseBuses::GetInfoStop(const string &stop) const {
    if (auto it = stop_in_buses.find(stop); it == stop_in_buses.end()) {
        return nullopt;
    } else {
        return it->second; // copy
    }
}

optional<const BusInfo> BaseBuses::GetInfoBus(const string &bus) const {
    if (auto it = buses.find(bus); it == buses.end()) {
        return nullopt;
    } else {
        return it->second; // copy
    }
}

void BaseBuses::BuildRouter(const Json::Dict& routing_settings_json) {
    router_ = make_unique<TransportRouter>(name_in_stop, buses, routing_settings_json);
}

std::optional<RouteInfo> BaseBuses::GetInfoRoute(const string &from, const string &to) const {
    return move(router_->GetInfoRoute(from, to));
}

std::string BaseBuses::GetInfoMap() const {
    return "NULL";
}

void BaseBuses::SetRenderSettings(const Json::Dict &settings) {
    router_map_ = make_unique<RouterMap>(settings);
}