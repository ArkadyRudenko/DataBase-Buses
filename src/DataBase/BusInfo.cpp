#include <ranges>
#include <algorithm>

#include "BusInfo.h"

using namespace std;
namespace rng = std::ranges;

const StopsList &BusInfo::getListStops() const {
    return busStops_;
}

Route BusInfo::getRoute() const {
    return route;
}

BusInfo::BusInfo(StopsList busStops)
        : busStops_(move(busStops)) {
    if ((*busStops_.begin())->name == busStops_.back()->name) {
        route = Route::ANNULAR;
    } else {
        route = Route::STRAIGHT;
        StopsList second_part;
        for (int i = busStops_.size() / 2; i >= 0; i--) {
            second_part.push_back(busStops_[i]);
        }
        rng::copy(second_part, back_inserter(busStops_));
    }
}




