
#include "BusInfo.h"

using namespace std;

const std::vector<std::string> &BusInfo::getListStops() const {
    return busStops_;
}

Route BusInfo::getRoute() const {
    return route;
}

BusInfo::BusInfo(std::vector<std::string> busStops)
        : busStops_(move(busStops)) {
    if (*(busStops_.begin()) == busStops_.back()) {
        route = Route::ANNULAR;
    } else {
        route = Route::STRAIGHT;
        // TODO optimaze copy
        // but maybe realocaton
        vector<string> second_part;
        for (int i = busStops_.size() / 2; i >= 0; i--) {
            second_part.push_back(busStops_[i]);
        }
        copy(second_part.begin(), second_part.end(), back_inserter(busStops_));
    }
}




