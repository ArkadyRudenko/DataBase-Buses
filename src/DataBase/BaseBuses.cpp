#include <cmath>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <optional>
#include <map>

#include "BaseBuses.h"

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
            BusStop new_bus_stop(stop.first, -1, -1); // later will be new values, other_stop`s tmp
            new_bus_stop.AddLength({busStop.name, stop.second});
            name_in_stop.insert({stop.first, new_bus_stop});
        }
    }
}


void BaseBuses::AddBus(const string bus,
                       const vector<string> stops, Route route) {
    StopsList busInfoList;

    for (auto &stop: stops) {
        stop_in_buses.find(stop)->second.insert(bus);
        busInfoList.push_back(make_shared<BusStop>(
                name_in_stop.find(stop)->second
        ));
    }
    BusInfo busInfo(busInfoList, route);
    busInfo.setRealLength(calcRealLength(busInfoList));
    busInfo.setCurvature(calcCurvature(busInfoList,busInfo.getRealLength()));
    busInfo.setCountUniqueStops(calcUniqueStops(busInfoList));
    //???????????????????
    buses.insert({bus, busInfo});
}

optional<const set<string>> BaseBuses::GetInfoStop(const std::string &stop) {
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

double BaseBuses::calcLength(StopsList stopsList) {
    double sum = 0;
    for (size_t i = 0; i < stopsList.size() - 1; i++) {
        sum += calcLengthBetweenTwoStops(stopsList[i].get(), stopsList[i + 1].get());
    }
    return sum;
}

double BaseBuses::calcLengthBetweenTwoStops(const BusStop *lhs, const BusStop *rhs) {
    return EARTH_RADIUS *
           acos(sin(calcRadians(lhs->latitude)) * sin(calcRadians(rhs->latitude)) +
                cos(calcRadians(lhs->latitude)) * cos(calcRadians(rhs->latitude))
                * cos(abs(calcRadians(lhs->longitude) - calcRadians(rhs->longitude))));
}

double BaseBuses::calcRadians(double value) {
    return (value * PI) / 180;
}

int BaseBuses::calcUniqueStops(const StopsList &stopsList) {
    map<string, int> names;
    for (const auto &stop: stopsList) {
        names[stop->name] = 0;
    }
    return names.size();
}

double BaseBuses::calcCurvature(const StopsList &stopsList, int64_t real_length) {
    return (real_length * 1.) / (calcLength(stopsList) * 1.);
}

int64_t BaseBuses::calcRealLength(const StopsList &stopsList) {
    int64_t sum = 0;
    for (int i = 0; i < stopsList.size() - 1; i++) {
        sum += (stopsList[i]->GetLengthByStop(stopsList[i + 1]->name));
    }
    return sum;
}
