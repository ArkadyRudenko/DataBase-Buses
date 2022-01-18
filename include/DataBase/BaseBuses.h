#pragma once

#include <unordered_map>
#include <memory>
#include <set>
#include <ranges>

#include "BusInfo.h"

struct CompareForBusStop {
    using is_transparent = void;  // Сделали компаратор прозрачным

    // Использовали стандартное сравнение для ключей
    bool operator()(const BusStop &lhs, const BusStop &rhs) const {
        return lhs.name < rhs.name;
    }
};


class BaseBuses {
public:

    void AddBus(std::string bus, std::pair<std::vector<std::string>, Route> stops_list);

    void AddStop(BusStop busStop);

    void GetInfoBus(const std::string& bus, std::ostream &os);
    void GetInfoStop(const std::string& stop, std::ostream &os);

private:
    std::unordered_map<std::string, BusInfo> buses;
    std::set<BusStop, CompareForBusStop> stops;

    constexpr static const double PI = 3.1415926535;
    constexpr static const int EARTH_RADIUS = 6371000;

    static double calcLength(StopsList stopsList);
    static double calcLengthBetweenTwoStops(const BusStop* lhs, const BusStop* rhs);
    static double calcRadians(double);
    static int calcUniqueStops(const StopsList& stopsList);
};

