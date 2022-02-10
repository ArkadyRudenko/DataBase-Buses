#pragma once

//
// Created by arkady on 10.02.2022.
//

#ifndef BASEBUSES_TRANSPORTROUTER_H
#define BASEBUSES_TRANSPORTROUTER_H

#include <memory>
#include <unordered_map>

#include "json.h"
#include "ItemPath.h"

#include "BusInfo.h"
#include "TransportRouter.h"
#include "Graph.h"
#include "Router.h"

using StopsDict = std::unordered_map<std::string, Stop>;
using BusesDict = std::unordered_map<std::string, BusInfo>;

class TransportRouter {
public:
    TransportRouter(const StopsDict&, const BusesDict&, const Json::Dict&);

    std::optional<RouteInfo> GetInfoRoute(const std::string&, const std::string&) const;
private:
    using BusGraph = Graph::DirectedWeightedGraph<double>;
    using Router = Graph::Router<double>;
    struct RoutSettings;

private:
    struct RoutSettings {
        int bus_wait_time; // in minutes
        double speed_of_bus; // km/h
    };

    RoutSettings route_settings_;

    // ??
    std::map<size_t, std::string> id_edge_in_bus;
    std::unordered_map<size_t, std::pair<Graph::Edge<double>, size_t>> id_in_edge_info;
    std::unordered_map<std::string, size_t> id_stops;
    std::unordered_map<size_t, std::string> id_stop_in_name_stop;

    void BuildGraph(const StopsDict&, const BusesDict&);
    static RoutSettings MakeRoutingSettings(const Json::Dict&);

    std::unique_ptr<Router> router;
    BusGraph graph;
};

#endif //BASEBUSES_TRANSPORTROUTER_H