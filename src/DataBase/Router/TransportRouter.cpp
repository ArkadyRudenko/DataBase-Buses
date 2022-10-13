//
// Created by arkady on 10.02.2022.
//

#include "TransportRouter.h"
#include "json.h"

using namespace std;

void TransportRouter::BuildGraph(const StopsDict &stops_dict,
                                 const BusesDict &buses_dict) {
    size_t index = 0;
    for (const auto &stop: stops_dict) {
        id_stops[stop.first] = index;
        id_stop_in_name_stop[index] = stop.first;
        index += 2;
    }
    // hardly unreadable fucking code TODO
    // see realisation Avtor`s
    for (const auto &bus: buses_dict) {
        const StopsList stops = bus.second.getListStops();
        for (int i = 0; i < stops.size() - 1; i++) {
            double weight = 0;
            size_t stops_count = 1;
            for (int j = (i + 1) % (stops.size() - 1);
                 j != i;
                 j = (j + 1) % (stops.size() - 1)) {

                const auto& next_stops = stops[
                        (j - 1) == -1 ? stops.size() - 2 : j - 1
                ]->getLengths();

                weight += (next_stops.find(stops[j]->name)->second * 1. * 60. / (route_settings_.speed_of_bus * 1000.));
                if (!(bus.second.getRoute() == Route::ANNULAR and j != 0 and j < i)) {
                    size_t id = graph.AddEdge({id_stops[stops[i]->name] + 1,
                                                id_stops[stops[j]->name],
                                                weight});

                    id_in_edge_info[id] = {graph.GetEdge(id), stops_count};
                    id_edge_in_bus[id] = bus.first;
                }
                stops_count++;
            }
            size_t id = graph.AddEdge({(id_stops[stops[i]->name]),
                                        id_stops[stops[i]->name] + 1,
                                        static_cast<double>(route_settings_.bus_wait_time)});
            id_in_edge_info[id] = {graph.GetEdge(id), 0};
            id_edge_in_bus[id] = bus.first;
        }
    }
}

TransportRouter::TransportRouter(const StopsDict& stops_dict,
                                 const BusesDict& buses_dict,
                                 const Json::Dict& routing_settings_json)
        : route_settings_(MakeRoutingSettings(routing_settings_json)) {
    graph = BusGraph(stops_dict.size() * 2);
    BuildGraph(stops_dict, buses_dict);
    router = make_unique<Router>(graph);
}

std::optional<RouteInfo> TransportRouter::GetInfoRoute(const string &from, const string &to) const {
    if (auto route = router->BuildRoute(id_stops.at(from), id_stops.at(to))) {
        RouteInfo route_info = {.total_time = route->weight};
        for (size_t i = 0; i < route->edge_count; i++) {
            Graph::EdgeId id = router->GetRouteEdge(route->id, i);
            if (id_in_edge_info.at(id).first.from % 2 == 0) {
                route_info.items.emplace_back(RouteInfo::WaitItem{
                        .stop_name = id_stop_in_name_stop.at(id_in_edge_info.at(id).first.from),
                        .time = static_cast<double>(route_settings_.bus_wait_time),
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

TransportRouter::RoutSettings TransportRouter::MakeRoutingSettings(const Json::Dict& json) {
    return {
            json.at("bus_wait_time").AsInt(),
            json.at("bus_velocity").AsDouble(),
    };
}