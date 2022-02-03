#include <ranges>
#include <algorithm>
#include <sstream>

#include "BaseBusesBuilder.h"
#include "AddBusCommand.h"
#include "AddStopCommand.h"

using namespace std;
using namespace Json;
//namespace rng = std::ranges;

BaseBuses BaseBusesBuilder::BuildBase(const vector<Node> &base_requests,
                                      const map<string, Node> &route_settings) {
    BaseBuses baseBuses;
    CreateCommands();

    baseBuses.setRouteSettings({route_settings.at("bus_wait_time").AsInt(),
                                route_settings.at("bus_velocity").AsDouble()});


    for (const auto &req: GetSortedRequests(base_requests)) {
        commands[req->AsMap().at("type").AsString()]->Execute(baseBuses, req->AsMap());
    }

    baseBuses.BuildGraph();
    baseBuses.BuildRouter();

    return baseBuses;
}

void BaseBusesBuilder::CreateCommands() {
    commands.insert({"Stop", make_shared<AddStopCommand>()});
    commands.insert({"Bus", make_shared<AddBusCommand>()});
}

vector<shared_ptr<Node>> GetSortedRequests(const vector<Node> &requests) {
    vector<shared_ptr<Node>> sorted_requests;

    sorted_requests.reserve(requests.size());
    for (const auto &req: requests) {
        sorted_requests.push_back(
                make_shared<Node>(req)
        );
    }

    partition(sorted_requests.begin(), sorted_requests.end(),
              [](shared_ptr<Node> &req) {
                  return req->AsMap().at("type").AsString() == "Stop";
              });
    return sorted_requests;
}