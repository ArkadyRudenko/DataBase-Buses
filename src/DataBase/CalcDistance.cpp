#include "CalcDistance.h"

using namespace std;

double calcLength(const StopsList& stopsList) {
    double sum = 0;
    for (size_t i = 0; i < stopsList.size() - 1; i++) {
        sum += calcLengthBetweenTwoStops(stopsList[i].get(), stopsList[i + 1].get());
    }
    return sum;
}

double calcLengthBetweenTwoStops(const Stop *lhs, const Stop *rhs) {
    return EARTH_RADIUS *
           acos(sin(calcRadians(lhs->latitude)) * sin(calcRadians(rhs->latitude)) +
                cos(calcRadians(lhs->latitude)) * cos(calcRadians(rhs->latitude))
                * cos(abs(calcRadians(lhs->longitude) - calcRadians(rhs->longitude))));
}

double calcRadians(double value) {
    return (value * PI) / 180;
}

int calcUniqueStops(const StopsList &stopsList) {
    map<string, int> names;
    for (const auto &stop: stopsList) {
        names[stop->name] = 0;
    }
    return names.size();
}

double calcCurvature(const StopsList &stopsList, int real_length) {
    return (real_length * 1.) / (calcLength(stopsList) * 1.);
}

int calcRealLength(const StopsList &stopsList) {
    int sum = 0;
    for (int i = 0; i < stopsList.size() - 1; i++) {
        sum += (stopsList[i]->GetLengthByStop(stopsList[i + 1]->name));
    }
    return sum;
}
