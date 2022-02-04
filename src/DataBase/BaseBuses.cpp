#include <cmath>
#include <sstream>
#include <algorithm>
#include <optional>

#include "BaseBuses.h"

using namespace std;

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


void BaseBuses::AddBus(const string &bus,
                       const vector<string> &stops, Route route) {
    StopsList busInfoList;

    for (auto &stop: stops) {
        stop_in_buses.find(stop)->second.insert(bus);
        busInfoList.push_back(make_shared<BusStop>(
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

optional<RouteInfo> BaseBuses::GetInfoRoute(const string &from, const string &to) const {
    if (auto route = router->BuildRoute(id_stops.at(from), id_stops.at(to))) {
        RouteInfo route_info = {.total_time = route->weight};
        for (size_t i = 0; i < route->edge_count; i++) {
            Graph::EdgeId id = router->GetRouteEdge(route->id, i);
            if (id_in_edge_info.at(id).first.from % 2 == 0) {
                route_info.items.emplace_back(RouteInfo::WaitItem{
                .stop_name = id_stop_in_name_stop.at(id_in_edge_info.at(id).first.from),
                .time = static_cast<double>(route_settings.waiting_minutes),
                });
            } else {
                route_info.items.emplace_back(RouteInfo::BusItem{
                        .bus_name = id_edge_in_bus.at(id),
                        .time = id_in_edge_info.at(id).first.weight,
                        .span_count = id_in_edge_info.at(id).second,
                });
            }
        }
        router->ReleaseRoute(route->id);
        return route_info;
    } else {
        return nullopt;
    }
}

void BaseBuses::BuildGraph() {
    graph = make_unique<Graph::DirectedWeightedGraph<double>>(name_in_stop.size() * 2);
    size_t index = 0;
    for (const auto &stop: name_in_stop) {
        id_stops[stop.first] = index;
        id_stop_in_name_stop[index] = stop.first;
        index += 2;
    }
    // hardly unreadable fucking code
    for (const auto &bus: buses) {
        const StopsList stops = bus.second.getListStops();
        for (size_t i = 0; i < stops.size() - 1; i++) {
            double weight = 0;
            size_t stops_count = 1;
            for (size_t j = (i + 1) % (stops.size() - 1);
                 j != i;
                 j = (j + 1) % (stops.size() - 1)) {

                const unordered_map<std::string, int> &next_stops = stops[
                        (j - 1) == -1 ? stops.size() - 2 : j - 1
                ]->getLengths();

                weight += (next_stops.find(stops[j]->name)->second * 1. * 60. / (route_settings.speed_of_bus * 1000.));
                if (!(bus.second.getRoute() == Route::ANNULAR and j != 0 and j < i)) {
                    size_t id = graph->AddEdge({id_stops[stops[i]->name] + 1,
                                                id_stops[stops[j]->name],
                                                weight});

                    id_in_edge_info[id] = {graph->GetEdge(id), stops_count};
                    id_edge_in_bus[id] = bus.first;
                }
                stops_count++;
            }
            size_t id = graph->AddEdge({(id_stops[stops[i]->name]),
                                        id_stops[stops[i]->name] + 1,
                                        static_cast<double>(route_settings.waiting_minutes)});
            id_in_edge_info[id] = {graph->GetEdge(id), 0};
            id_edge_in_bus[id] = bus.first;
        }
    }
}

void BaseBuses::BuildRouter() {
    router = make_unique<Graph::Router<double>>(*graph);
}
