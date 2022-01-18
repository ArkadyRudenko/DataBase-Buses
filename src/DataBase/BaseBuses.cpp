#include <cmath>
#include <sstream>
#include <iomanip>
#include <algorithm>

#include "BaseBuses.h"

using namespace std;
namespace rng = std::ranges;


void BaseBuses::AddBus(int bus, std::vector<std::string> stops_list) {
    StopsList busInfoList;
    for (auto &stop: stops_list) {
        busInfoList.push_back(make_shared<BusStop>(
                *rng::find_if(stops, [&](const BusStop &bus_stop) {
                    return bus_stop.name == stop;
                })
        ));
    }
    buses.insert({bus, move(BusInfo(busInfoList))}); // TODO move need???
}


void BaseBuses::AddStop(BusStop busStop) {
    stops.insert(std::move(busStop));
}


void BaseBuses::GetInfoBus(int bus, std::ostream &os) {
    os << "Bus " << bus << ": ";
    if (!buses.contains(bus)) {
        os << "not found\n";
    } else {
        const StopsList &stops_bus = buses.at(bus).getListStops();

        os << stops_bus.size() << " stops on route, " <<
           ((buses.at(bus).getRoute() == Route::ANNULAR) ? stops_bus.size() - 1 : (stops_bus.size() / 2 + 1))
           << " unique stops, ";
        os << setprecision(6) << calcLength(stops_bus) << " route length\n";
    }
}

double BaseBuses::calcLength(StopsList stopsList) {
    double sum = 0;
    for (size_t i = 0; i < stopsList.size() - 1; i++) {
        sum += calcLengthBetweenTwoStops(stopsList[i].get(), stopsList[i + 1].get());
    }
    return sum;
}

double BaseBuses::calcLengthBetweenTwoStops(const BusStop *lhs, const BusStop *rhs) {
    return EARTH_RADIUS *
           acos(sin(calcRadians(lhs->latitude)) * sin(calcRadians(rhs->latitude)) +
                cos(calcRadians(lhs->latitude)) * cos(calcRadians(rhs->latitude))
                * cos(abs(calcRadians(lhs->longitude) - calcRadians(rhs->longitude))));
}

double BaseBuses::calcRadians(double value) {
    return (value * PI) / 180;
}
