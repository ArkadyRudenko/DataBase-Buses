#include <ranges>
#include <algorithm>
#include <iterator>

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
        move(second_part.begin(), second_part.end(), back_inserter(busStops_));
    }
}

int64_t BusInfo::getRealLength() const {
    return real_length;
}

void BusInfo::setRealLength(int64_t realLength) {
    real_length = realLength;
}

double BusInfo::getCurvature() const {
    return curvature;
}

void BusInfo::setCurvature(double curvature) {
    BusInfo::curvature = curvature;
}

int BusInfo::getCountUniqueStops() const {
    return count_unique_stops;
}

void BusInfo::setCountUniqueStops(int countUniqueStops) {
    count_unique_stops = countUniqueStops;
}

size_t BusInfo::GetCountStops() const {
    return busStops_.size();
}




