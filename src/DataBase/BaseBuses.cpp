#include <cmath>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <map>

#include "BaseBuses.h"

using namespace std;
//namespace rng = std::ranges;


void BaseBuses::AddBus(string bus, std::pair<std::vector<std::string>, Route> stops_list) {
    StopsList busInfoList;
    for (auto &stop: stops_list.first) {
        busInfoList.push_back(make_shared<BusStop>(
                // TODO rng
                *find_if(stops.begin(), stops.end(), [&](const BusStop &bus_stop) {
                    return bus_stop.name == stop;
                })
        ));
    }
    buses.insert({bus, move(BusInfo(busInfoList, stops_list.second))}); // TODO move need???
}


void BaseBuses::AddStop(BusStop busStop) {
    stops.insert(std::move(busStop));
}


void BaseBuses::GetInfoBus(string bus, std::ostream &os) {
    os << "Bus " << bus << ": ";
    auto it = buses.find(bus);
    if (it == buses.end()) {
        os << "not found\n";
    } else {
        const StopsList &stops_bus = buses.at(bus).getListStops();

        os << stops_bus.size() << " stops on route, " <<
           calcUniqueStops(stops_bus)
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

int BaseBuses::calcUniqueStops(const StopsList &stopsList) {
    map<string, int> names;
    for (const auto &stop: stopsList) {
        names[stop->name] = 0;
    }
    return names.size();
}
