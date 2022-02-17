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
#include "json.h"
#include "ItemPath.h"
#include "TransportRouter.h"
#include "Router.h"
#include "RouterMap.h"


using StopsDict = std::unordered_map<std::string, Stop>;
using BusesDict = std::unordered_map<std::string, BusInfo>;

class BaseBuses {
public:

    void AddBus(const std::string &, const std::vector<std::string> &, Route);

    void AddStop(const Stop &);

    std::optional<const BusInfo> GetInfoBus(const std::string &) const;

    std::optional<const std::set<std::string>> GetInfoStop(const std::string &) const;

    std::optional<RouteInfo> GetInfoRoute(const std::string &, const std::string &) const;

    std::string GetInfoMap() const;

private:
    BusesDict buses;
    StopsDict name_in_stop;
    std::unordered_map<std::string, std::set<std::string>> stop_in_buses;

    explicit BaseBuses() = default;
    void BuildRouter(const Json::Dict&);
    void SetRenderSettings(const Json::Dict&);

    std::unique_ptr<TransportRouter> router_;
    std::unique_ptr<RouterMap> router_map_;

    friend class BaseBusesBuilder;
};