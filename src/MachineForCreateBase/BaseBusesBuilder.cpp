#include <ranges>
#include <algorithm>
#include <sstream>

#include "BaseBusesBuilder.h"
#include "AddBusCommand.h"
#include "AddStopCommand.h"

using namespace std;
using namespace nlohmann;
//namespace rng = std::ranges;

BaseBuses BaseBusesBuilder::BuildBase(const json &base_requests) {
    BaseBuses baseBuses;
    CreateCommands();

    for(const auto& req : GetSortedRequests(base_requests)) {
        commands[req->at("type").get<string>()]->Execute(baseBuses, *req);
    }

    return baseBuses;
}

void BaseBusesBuilder::CreateCommands() {
    commands.insert({"Stop", make_shared<AddStopCommand>()});
    commands.insert({"Bus", make_shared<AddBusCommand>()});
}

vector<shared_ptr<json>> GetSortedRequests(const json &requests) {
    vector<shared_ptr<json>> sorted_requests;

    for (const auto &req: requests) {
        sorted_requests.push_back(
                make_shared<json>(req)
        );
    }

    partition(sorted_requests.begin(), sorted_requests.end(),
              [](shared_ptr<json> &req) {
                  return req->at("type") == "Stop";
              });
    return sorted_requests;
}