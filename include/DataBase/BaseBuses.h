#pragma once

#include <memory>
#include <map>
#include <ranges>
#include <optional>
#include <unordered_map>
#include <set>
#include <string>

#include "BusInfo.h"
#include "Graph.h"
#include "Router.h"
#include "ItemPath.h"

class BaseBuses {
public:
    explicit BaseBuses() = default;

    void AddBus(const std::string &, const std::vector<std::string> &, Route);

    void AddStop(const BusStop &);

    std::optional<const BusInfo> GetInfoBus(const std::string &);

    std::optional<const std::set<std::string>> GetInfoStop(const std::string &);

    std::optional<std::vector<ItemPath>> GetInfoRoute(const std::string& from, const std::string& to);

private:
    std::unordered_map<std::string, BusInfo> buses;
    std::unordered_map<std::string, BusStop> name_in_stop;
    std::unordered_map<std::string, std::set<std::string>> stop_in_buses;

    std::unique_ptr<Graph::DirectedWeightedGraph<double>> graph;
    std::unique_ptr<Graph::Router<double>> router;

    // ???
    std::map<size_t, std::string> id_edge_in_bus;
    std::unordered_map<size_t, std::pair<Graph::Edge<double>, size_t>> id_in_edge_info;
    std::unordered_map<std::string, size_t> id_stops;
    std::unordered_map<size_t, std::string> id_stop_in_name_stop;
    // ???

    friend class BaseBusesBuilder;

private:

    struct RoutSettings {
        int waiting_minutes;
        double speed_of_bus;
    };

    RoutSettings route_settings;

    void setRouteSettings(const RoutSettings &routeSettings) {
        route_settings = routeSettings;
    }

    void BuildGraph();
    void BuildRouter();
};