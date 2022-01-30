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

    int getRealLength() const;

    double getCurvature() const;
    int getCountUniqueStops() const;

    int GetCountStops() const ;

private:
    StopsList busStops_;
    Route route_;
    int real_length;
    double curvature;
    int count_unique_stops;
};

