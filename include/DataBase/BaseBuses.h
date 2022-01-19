#pragma once

#include <unordered_map>
#include <memory>
#include <set>
#include <ranges>

#include "BusInfo.h"

class BaseBuses {
public:

    void AddBus(const std::string& bus, const std::pair<std::vector<std::string>, Route>& stops_list);

    void AddStop(const BusStop& busStop);

    void GetInfoBus(const std::string& bus, std::ostream &os);

    void GetInfoStop(const std::string& stop, std::ostream &os);

private:
    std::unordered_map<std::string, BusInfo> buses;
    std::unordered_map<std::string, BusStop> name_in_stop;
    std::unordered_map<std::string, std::set<std::string>> stop_in_buses;

    constexpr static const double PI = 3.1415926535;
    constexpr static const int EARTH_RADIUS = 6371000;

    static double calcLength(StopsList stopsList);
    static double calcLengthBetweenTwoStops(const BusStop* lhs, const BusStop* rhs);
    static double calcRadians(double);
    static int calcUniqueStops(const StopsList& stopsList);
};

