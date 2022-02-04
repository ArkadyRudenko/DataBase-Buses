#include <algorithm>
#include <iterator>

#include "BusInfo.h"
#include "CalcDistance.h"

using namespace std;

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
        }
        move(second_part.begin(), second_part.end(), back_inserter(busStops_));
    }
    real_length = calcRealLength(busStops_);
    curvature = calcCurvature(busStops_, real_length);
    count_unique_stops = calcUniqueStops(busStops_);
}

int BusInfo::getRealLength() const {
    return real_length;
}

double BusInfo::getCurvature() const {
    return curvature;
}

int BusInfo::getCountUniqueStops() const {
    return count_unique_stops;
}

int BusInfo::GetCountStops() const {
    return busStops_.size();
}