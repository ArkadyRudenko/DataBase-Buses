#include <cmath>
#include <sstream>
#include <algorithm>
#include <optional>
#include <memory>

#include "BaseBuses.h"
#include "TransportRouter.h"

using namespace std;

void BaseBuses::AddStop(const Stop& busStop) {
  if (auto it = stops_dict.find(busStop.name); it != stops_dict.end()) { // bad process
    it->second.SplitTwoMaps(busStop.getLengths());
    it->second.SetCoordinates(busStop.latitude, busStop.longitude);
  } else {
    stops_dict.insert({busStop.name, busStop});
  }
  stop_in_buses.insert({busStop.name, {}});

  const auto& lengths = busStop.getLengths();
  for (const auto& stop : lengths) {
    if (auto other_stop = stops_dict.find(stop.first); other_stop != stops_dict.end()) {
      other_stop->second.AddLength({busStop.name, stop.second});
    } else {
      Stop new_bus_stop(stop.first, -181, -181); // later will be new values, other_stop`s tmp
      new_bus_stop.AddLength({busStop.name, stop.second});
      stops_dict.insert({stop.first, new_bus_stop});
    }
  }
}

void BaseBuses::AddBus(const string& bus,
                       const vector<string>& stops, Route route) {
  StopsList busInfoList;

  for (auto& stop : stops) {
    stop_in_buses.find(stop)->second.insert(bus);
    busInfoList.push_back(make_shared<Stop>(
        stops_dict.find(stop)->second
    ));
  }
  buses_dict.insert({bus, BusInfo(move(busInfoList), route)});
}

optional<const set<string>> BaseBuses::GetInfoStop(const string& stop) const {
  if (auto it = stop_in_buses.find(stop); it == stop_in_buses.end()) {
    return nullopt;
  } else {
    return it->second; // copy
  }
}

optional<const BusInfo> BaseBuses::GetInfoBus(const string& bus) const {
  if (auto it = buses_dict.find(bus); it == buses_dict.end()) {
    return nullopt;
  } else {
    return it->second; // copy
  }
}

void BaseBuses::BuildRouter(const Json::Dict& routing_settings_json) {
  router_ = make_unique<TransportRouter>(stops_dict, buses_dict, routing_settings_json);
}

std::optional<RouteInfo> BaseBuses::GetInfoRoute(const string& from, const string& to) const {
  return move(router_->GetInfoRoute(from, to));
}

std::string BaseBuses::GetInfoMap() const {
  stringstream out;
  map_.Render(out);
//    return out.str();
  string result_svg;
  for (const char ch : out.str()) {
    if (ch == '\"' or ch == '\\') {
      result_svg.push_back('\\');
    }
    result_svg.push_back(ch);
  }
//    string res;
//    for(char ch : result_svg) {
//        if(ch != 92) {
//            res += ch;
//        }
//    }
//    cout << "\n WORKING VERSION=\n" << res << '\n';
  return result_svg;
}
/*
for (const char ch: ss.str()) {
if (ch == '\"' or ch == '\\') {
    result_svg.push_back('\\');
}
result_svg.push_back(ch);
 }
} */

void BaseBuses::BuildMap(const Json::Node& render_settings_json) {
  map_ = MapRenderer(stops_dict, buses_dict, render_settings_json).Render();
}

