#pragma once

#include <vector>
#include <string>
#include <iostream>

#include "BusStop.h"
#include <memory>

enum Route {
    ANNULAR = 0,
    STRAIGHT
};

using StopsList = std::vector<std::shared_ptr<BusStop>>;

class BusInfo {
public:
    explicit BusInfo(StopsList busStops, Route route);

    const StopsList &getListStops() const;

    Route getRoute() const;

    int64_t getRealLength() const;

    void setRealLength(int64_t realLength);

    double getCurvature() const;

    void setCurvature(double curvature);

    int getCountUniqueStops() const;

    void setCountUniqueStops(int countUniqueStops);

    size_t GetCountStops() const ;

private:
    StopsList busStops_;
    Route route_;
    int64_t real_length;
    double curvature;
    int count_unique_stops;
};

