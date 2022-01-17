#include <cmath>
#include <sstream>
#include <iomanip>

#include "BaseBuses.h"

using namespace std;

void BaseBuses::AddBus(int bus, BusInfo busInfo) {
    buses.insert({bus, std::move(busInfo)});
}

void BaseBuses::AddStop(BusStop busStop) {
    stops.insert(std::move(busStop));
}


void BaseBuses::GetInfoBus(int bus, std::ostream &os) {
    os << "Bus " << bus << ": ";
    if (!buses.contains(bus)) {
        os << "not found\n";
    } else {
        const vector<string>& stops_bus = buses.at(bus).getListStops();
        Route route_bus = buses.at(bus).getRoute();
        CalculateLength calculateLength(stops_bus, stops);

        os << stops_bus.size() << " stops on route, " <<
           ((route_bus == Route::ANNULAR) ? stops_bus.size() - 1 : (stops_bus.size() / 2 + 1))
           << " unique stops, ";
        os << setprecision(6) << calculateLength.calcLength() << " route length\n";
    }
}


double BaseBuses::CalculateLength::calcLength() {
    double sum = 0;
    for (size_t i = 0; i < stops_path.size() - 1; i++) {
        sum += calcLengthBetweenTwoStops(i, i + 1);
    }
    return sum;
}

double BaseBuses::CalculateLength::calcLengthBetweenTwoStops(size_t first, size_t second) {
    auto it1 = find_if(stops_coordinate_path.begin(), stops_coordinate_path.end(),
                      [&](const BusStop& busStop) {
                          return busStop.name == stops_path[first];
                      });
    auto it2 = find_if(stops_coordinate_path.begin(), stops_coordinate_path.end(),
                      [&](const BusStop& busStop) {
                          return busStop.name == stops_path[second];
                      });
    double f1 = it1->latitude * PI / 180;
    double l1 = it1->longitude * PI / 180;
    double f2 = it2->latitude * PI / 180;
    double l2 = it2->longitude * PI / 180;
    double deltaL = abs(l1 - l2);
    double res =
            EARTH_RADIUS * acos(sin(f1) * sin(f2) + cos(f1) * cos(f2) * cos(deltaL));
    return res;
}

/*
 * Транспортный справочник, часть A
По какой формуле считать расстояние между точками?
 */
