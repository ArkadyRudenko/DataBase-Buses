#include <ranges>
#include <algorithm>
#include <sstream>

#include "BaseBusesBuilder.h"
#include "AddBusCommand.h"
#include "AddStopCommand.h"

using namespace std;
using namespace Json;
//namespace rng = std::ranges;

BaseBuses BaseBusesBuilder::BuildBase(const Node &base_requests) {
    BaseBuses baseBuses;
    CreateCommands();

    for(const auto& req : GetSortedRequests(base_requests)) {
        commands[req->AsMap().at("type").AsString()]->Execute(baseBuses, req->AsMap());
    }

    return baseBuses;
}

void BaseBusesBuilder::CreateCommands() {
    commands.insert({"Stop", make_shared<AddStopCommand>()});
    commands.insert({"Bus", make_shared<AddBusCommand>()});
}

vector<shared_ptr<Node>> GetSortedRequests(const Json::Node &requests) {
    vector<shared_ptr<Node>> sorted_requests;

    for (const auto &req: requests.AsArray()) {
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