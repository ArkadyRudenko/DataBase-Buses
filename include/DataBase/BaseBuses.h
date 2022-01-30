#pragma once

#include <unordered_map>
#include <memory>
#include <set>
#include <ranges>
#include <optional>

#include "BusInfo.h"

class BaseBuses {
public:

    void AddBus(const std::string&, const std::vector<std::string>&, Route);

    void AddStop(const BusStop&);

    std::optional<const BusInfo> GetInfoBus(const std::string&);

    std::optional<const std::set<std::string>> GetInfoStop(const std::string&);

    std::optional<int> GetInfoRoute();

private:
    std::unordered_map<std::string, BusInfo> buses;
    std::unordered_map<std::string, BusStop> name_in_stop;
    std::unordered_map<std::string, std::set<std::string>> stop_in_buses;
};

