#include <ranges>
#include <algorithm>

#include "BusInfo.h"

using namespace std;
//namespace rng = std::ranges;

const StopsList &BusInfo::getListStops() const {
    return busStops_;
}

Route BusInfo::getRoute() const {
    return route_;
}

BusInfo::BusInfo(StopsList busStops, Route route)
        : busStops_(move(busStops)), route_(route) {
    if (route != Route::ANNULAR) {
        StopsList second_part;
        for (int i = busStops_.size() - 2; i >= 0; i--) {
            second_part.push_back(busStops_[i]);
        } // TODO rng
        copy(second_part.begin(), second_part.end(), back_inserter(busStops_));
    }
}




