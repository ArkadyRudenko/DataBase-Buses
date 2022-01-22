#include <sstream>
#include <vector>

#include "AddBusCommand.h"
#include "PasreRequests.h"


using namespace std;

void AddBusCommand::Execute(BaseBuses &baseBuses, nlohmann::json & bus) {
    baseBuses.AddBus(bus["name"].get<string>(),
                     CreateVectorStops(bus["stops"]),
                     GetRoute(bus["is_roundtrip"]));
}

std::vector<std::string> CreateVectorStops(const nlohmann::json &stops) {
    vector<string> res;
    for (const auto &stop: stops.get<vector<string>>()) {
        res.push_back(stop);
    }
    return res;
}

Route GetRoute(const nlohmann::json& route) {
    return route.get<bool>() ? Route::ANNULAR : Route::STRAIGHT;
}