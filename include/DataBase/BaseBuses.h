#pragma once

#include <unordered_map>
#include <memory>
#include <set>
#include <ranges>

#include "BusInfo.h"

namespace rng = std::ranges;

struct Bus {
    int number;

    explicit Bus(int v) : number(v) {}
};

struct CompareForBusStop {
    using is_transparent = void;  // Сделали компаратор прозрачным

    // Использовали стандартное сравнение для ключей
    bool operator()(const BusStop &lhs, const BusStop &rhs) const {
        return lhs.name < rhs.name;
    }
};


class BaseBuses {
public:

    void AddBus(int bus, std::vector<std::string> stops_list);

    void AddStop(BusStop busStop);

    void GetInfoBus(int bus, std::ostream &os);

private:
    std::unordered_map<int, BusInfo> buses;
    std::set<BusStop, CompareForBusStop> stops;

    constexpr static const double PI = 3.1415926535;
    constexpr static const int EARTH_RADIUS = 6371000;

    static double calcLength(StopsList stopsList);
    static double calcLengthBetweenTwoStops(const BusStop* lhs, const BusStop* rhs);
    static double calcRadians(double);
};

