#pragma once

#include <vector>
#include <string>
#include <iostream>

#include "BusStop.h"

enum Route {
    ANNULAR = 0,
    STRAIGHT
};

class BusInfo {
public:
    explicit BusInfo(std::vector<std::string> busStops);

    const std::vector<std::string> &getListStops() const;

    Route getRoute() const;

private:
    std::vector<std::string> busStops_;
    Route route;
};

