#pragma once

#include "BusInfo.h"
#include "Stop.h"

#include <cmath>
#include <map>

constexpr static const double PI = 3.1415926535;
constexpr static const int EARTH_RADIUS = 6371000;

double calcLength(const StopsList&);
double calcLengthBetweenTwoStops(const Stop*, const Stop*);
double calcRadians(double);
int calcUniqueStops(const StopsList&);
double calcCurvature(const StopsList&, int);
int calcRealLength(const StopsList&);