//
// Created by arkady on 30.01.2022.
//

#include <string>

#include "GetRouteInfo.h"
#include "ItemPath.h"
#include "json.h"

using namespace Json;
using namespace std;

void GetRouteInfo::Listen(BaseBuses &baseBuses,
                          const std::map<std::string, Json::Node> &route_settings,
                          std::ostream &os) {
    Node res;
    res.push_back("request_id"s, route_settings.at("id").AsInt());
    if (auto items = baseBuses.GetInfoRoute(route_settings.at("from").AsString(),
                                            route_settings.at("to").AsString())) {
        vector<Node> items_of_path;
        double total_time = 0;
        for(const auto& item : *items) {
            if(item.type == EdgeType::WAIT) {
                Node node_wait;
                node_wait.push_back("type"s, "Wait");
                node_wait.push_back("stop_name"s, item.name);
                node_wait.push_back("time"s, item.time);
                items_of_path.push_back(node_wait);
                total_time += item.time;
            } else {
                Node node_bus;
                node_bus.push_back("type"s, "Bus");
                node_bus.push_back("bus"s, item.name);
                node_bus.push_back("time"s, item.time);
                node_bus.push_back("span_count"s, static_cast<int>(item.span_count));
                items_of_path.push_back(node_bus);
                total_time += item.time;
            }
        }
        Node final_items;
        for(const auto& i : items_of_path) {
            final_items.push_back(i);
        }
        res.push_back("items"s, final_items);
        res.push_back("total_time"s, total_time);
    } else {
        res.push_back("error_message"s, "not found"s);
    }

    os << res;
}
